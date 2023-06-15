#include "minishell.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>

t_list	**_get_garbage(); //@toddo A CHECKER;

int	cpy_cmd(char *cmd, char **addr)
{
	char	*res;
	int		i;

	i = 0;
	while (cmd[i] && cmd[i] != ' ')
		i++;
	res = my_malloc((i + 1) * sizeof(char));
	if (!res)
		exit(MALLOC_FAIL_ERRNO);
	i = -1;
	while (cmd[++i] && cmd[i] != ' ')
		res[i] = cmd[i];
	res[i] = 0;
	*addr = res;
	return (i);
}

void	cmd_child(t_cmd cmd, char *path, t_context *context)
{
	set_children_signals();
	context->in_fork = true;
	if (cmd.input_fd >= 0)
		dup2(cmd.input_fd, STDIN_FILENO);
	if (cmd.output_fd >= 0)
		dup2(cmd.output_fd, STDOUT_FILENO);
	if ((execve(path, cmd.cmd, context->env.tab)) < 0)
		error(EXECVE_FAIL_ERRNO, __LINE__, __FILE__);
	//free_all(_get_garbage());
}

void	child_exit_status(int res, t_context *context)
{
	if (WIFEXITED(res))
		context->exit_value = WEXITSTATUS(res);
	else if (WIFSIGNALED(res))
	{
		context->exit_value = 128 + WTERMSIG(res);
		if (WTERMSIG(res) == SIGINT)
		{
			printf_fd(STDERR_FILENO, "\n");
			context->stop = true;
		}
		else if (WTERMSIG(res) == SIGQUIT)
			printf_fd(STDERR_FILENO, "Quit (core dumped)\n");
	}
	else
		context->exit_value = 1;
}

void	set_underscore_env(t_context *context, char **cmd)
{
	if (!*cmd)
		return ;
	while (*(cmd + 1))
		cmd++;
	add_env(&context->env, "_", *cmd);
}

void	exec_cmd(char *start, int len, t_context *context)
{
	t_cmd	cmd;
	int		cpid;
	int		res;

	if (init_commande(&cmd, start, len, context))
		return ;
	if (cmd.input_fd < 0 || cmd.output_fd < 0)
	{
		context->exit_value = 1;
		return ;
	}
	set_underscore_env(context, cmd.cmd);
	if (!cmd.path)
	{
		context->exit_value
			= exec_builtin(cmd, context, cmd.output_fd, cmd.input_fd);
	}
	else
	{
		cpid = fork();
		if (cpid < 0)
			error(FORK_FAIL_ERRNO, __LINE__, __FILE__);
		if (!cpid)
			cmd_child(cmd, cmd.path, context);
		set_wait_signals();
		waitpid(cpid, &res, 0);
		set_parent_signals();
		child_exit_status(res, context);
		}
}

//	@TODO change i system ? -> for now :
//		i == 0 == FIRST_PIPE
//		i == 1 == MIDDLE_PIPE
//		i == 2 == LAST_PIPE
void	pipe_child(int pipefd[2], int precedent_fd, char *cmd, int i, t_context *context)
{
	context->in_fork = true;
	if (i != 2 && close(pipefd[0]) < 0)
		error(CLOSE_FAIL_ERRNO, __LINE__, __FILE__);
	if (i != 0 && dup2(precedent_fd, STDIN_FILENO) < 0)
		error(DUP2_FAIL_ERRNO, __LINE__, __FILE__);
	if (i != 0 && close(precedent_fd) < 0)
		error(CLOSE_FAIL_ERRNO, __LINE__, __FILE__);
	if (i != 2 && dup2(pipefd[1], STDOUT_FILENO) < 0)
		error(DUP2_FAIL_ERRNO, __LINE__, __FILE__);
	if (i != 2 && close(pipefd[1]) < 0)
		error(CLOSE_FAIL_ERRNO, __LINE__, __FILE__);
	exec_cmd(cmd, ft_strlen(cmd), context);
	exit(context->exit_value);
}

void	wait_children(int *cpids, const int cmds_count, t_context *context)
{
	int	exit_value;
	int	i;

	i = -1;
	set_wait_signals();
	while (++i < cmds_count)
		waitpid(cpids[i], &exit_value, 0);
	set_parent_signals();
	child_exit_status(exit_value, context);
}

void	exec_pipe(t_block *input, t_context *context)
{
	char		**cmds_tab;
	int			*cpids;
	int			pipefd[2];
	int			precedent_fd;
	const int	cmds_count = count_block(input);
	int			i;

	cmds_tab = get_tab_block(input);
	cpids = my_malloc(cmds_count * sizeof(int));
	i = 0;
	while (i < cmds_count)
	{
		if (i != cmds_count - 1 && pipe(pipefd) < 0)
			error(PIPE_FAIL_ERRNO, __LINE__, __FILE__);
		cpids[i] = fork();
		if (cpids[i] < 0)
			error(FORK_FAIL_ERRNO, __LINE__, __FILE__);
		if (!cpids[i])
			pipe_child(pipefd, precedent_fd, cmds_tab[i], (!!i) + (i == cmds_count - 1), context);
		if (i != cmds_count - 1 && close(pipefd[1]) < 0)
			error(CLOSE_FAIL_ERRNO, __LINE__, __FILE__);
		if (i > 0 && close(precedent_fd) < 0)
			error(CLOSE_FAIL_ERRNO, __LINE__, __FILE__);
		if (i != cmds_count - 1)
			precedent_fd = pipefd[0];
		i++;
	}
	wait_children(cpids, cmds_count, context);
}

void	exec_block(t_block *input, t_context *context)
{
	if (context->stop)
		return ;
	if (input->op == NO_OP)
	{
		exec_cmd(input->start, input->len, context);
		return ;
	}
	if (input->op == PP)
	{
		exec_pipe(input, context);
		return ;
	}
	if (input->op == OR)
	{
		exec_block(input->left, context);
		if (context->exit_value)
			exec_block(input->right, context);
		return ;
	}
	if (input->op == AND)
	{
		exec_block(input->left, context);
		if (!context->exit_value)
			exec_block(input->right, context);
		return ;
	}
	error_str("exec_block: undefined operator", __LINE__, __FILE__);
}
