#include "minishell.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>

// @TODO rm
int	cpy_cmd(char *cmd, char **addr)
{
	char	*res;
	int		i;

	i = 0;
	while (cmd[i] && cmd[i] != ' ')
		i++;
	res = malloc((i + 1) * sizeof(char));
	if (!res)
		exit(MALLOC_FAIL_ERRNO);
	i = -1;
	while (cmd[++i] && cmd[i] != ' ')
		res[i] = cmd[i];
	res[i] = 0;
	*addr = res;
	return (i);
}

// @TODO Improve
int	parse(t_cmd *cmd, char *str, int len)
{
	char	*file;
	int		i;
	int		j;

	enum {CMD, ARG, INFILE, OUTFILE, OUTIFLE_APPEND} type = CMD;
	*cmd = (t_cmd){NULL, ft_calloc(10, sizeof(char *)), -1, -1}; // !!!!!!!!!!!!! MAX 10 ARGS
	i = 0;
	j = 0;
	while (i < len)
	{
		while (str[i] == ' ')
			i++;
		if (i == len)
			break ;
		if (str[i] == '<')
			type = INFILE;
		else if (str[i] == '>' && str[i + 1] == '>')
			type = OUTIFLE_APPEND;
		else if (str[i] == '>')
			type = OUTFILE;
		else if (type == CMD)
		{
			type = ARG;
			i += cpy_cmd(str + i, &cmd->cmd);
		}
		else if (type == ARG)
			i += cpy_cmd(str + i, &cmd->args[j++]);
		else if (type == INFILE)
		{
			if (cmd->input_fd != -1 && close(cmd->input_fd))
				error(CLOSE_FAIL_ERRNO);
			i += cpy_cmd(str + i, &file);
			cmd->input_fd = open(file, O_RDONLY);
			if (cmd->input_fd == -1)
			{
				perror("minishell");
				return (1);
			}
			free(file);
		}
		else if (type == OUTFILE || type == OUTIFLE_APPEND)
		{
			if (cmd->output_fd != -1 && close(cmd->output_fd))
				error(CLOSE_FAIL_ERRNO);
			i += cpy_cmd(str + i, &file);
			cmd->output_fd = open(file, O_WRONLY | O_CREAT | (O_APPEND * (type == OUTIFLE_APPEND)) | (O_TRUNC * !(type == OUTIFLE_APPEND)), S_IRWXU | S_IRGRP | S_IXGRP | S_IXOTH);
			free(file);
		}
		i++;
	}
	return (0);
}

char	*get_cmd_path(char *cmd)
{
	// @TODO check absolute path, relative path or PATH, check if exists, execution rights, ..
	// @TODO reimplement from 0
	char				*res = malloc(ft_strlen(cmd) + 1 + ft_strlen("/bin/"));
	unsigned long		i;

	i = 0;
	while (i < ft_strlen("/bin/"))
	{
		res[i] = "/bin/"[i];
		i++;
	}
	while (i < ft_strlen(cmd) + ft_strlen("/bin/"))
	{
		res[i] = cmd[i - ft_strlen("/bin/")];
		i++;
	}
	res[i] = 0;
	return (res);
}

void	cmd_child(t_cmd cmd, char *path, t_context *context)
{
	if (cmd.input_fd >= 0)
		dup2(cmd.input_fd, STDIN_FILENO);
	if (cmd.output_fd >= 0)
		dup2(cmd.output_fd, STDOUT_FILENO);
	if ((execve(path, cmd.args, context->env.tab)) < 0)
		error(EXECVE_FAIL_ERRNO);
}

int	exec_cmd(char *start, int len, t_context *context)
{
	t_cmd	cmd;
	char	*cmd_path;
	int		cpid;
	int		res;

	parse(&cmd, start, len);
	// @TODO check for builtin and separate in different function
	cmd_path = get_cmd_path(cmd.cmd);
	cpid = fork();
	if (cpid < 0)
		error(FORK_FAIL_ERRNO);
	if (!cpid)
		cmd_child(cmd, cmd_path, context);
	waitpid(cpid, &res, 0);
	return (res);
}

//	@TODO change i system ? -> for now :
//		i == 0 == FIRST_PIPE
//		i == 1 == MIDDLE_PIPE
//		i == 2 == LAST_PIPE
void	pipe_child(int pipefd[2], int precedent_fd, char *cmd, int i, t_context *context)
{
	if (close(pipefd[0]) < 0)
		error(CLOSE_FAIL_ERRNO);
	if (i != 0 && dup2(precedent_fd, STDIN_FILENO) < 0)
		error(DUP2_FAIL_ERRNO);
	if (i != 0 && close(precedent_fd) < 0)
		error(CLOSE_FAIL_ERRNO);
	if (i != 2 && dup2(pipefd[1], STDOUT_FILENO) < 0)
		error(DUP2_FAIL_ERRNO);
	if (i != 2 && close(pipefd[1]) < 0)
		error(CLOSE_FAIL_ERRNO);
	exit(exec_cmd(cmd, ft_strlen(cmd), context));
}

int	wait_children(int *cpids, const int cmds_count)
{
	int	exit_value;
	int	i;

	i = -1;
	while (++i < cmds_count)
		waitpid(cpids[i], &exit_value, 0);
	return (exit_value);
}

int	exec_pipe(t_block *input, t_context *context)
{
	char		**cmds_tab;
	int			*cpids;
	int			pipefd[2];
	int			precedent_fd;
	const int	cmds_count = count_block(input);
	int			i;

	cmds_tab = get_tab_block(input, &context->garb);
	cpids = my_malloc(cmds_count * sizeof(int), &context->garb);
	i = 0;
	while (i < cmds_count)
	{
		if (i != cmds_count - 1 && pipe(pipefd) < 0)
			error(PIPE_FAIL_ERRNO);
		cpids[i] = fork();
		if (cpids[i] < 0)
			error(FORK_FAIL_ERRNO);
		if (!cpids[i])
			pipe_child(pipefd, precedent_fd, cmds_tab[i], !!i + i == cmds_count - 1, context);
		if (i != cmds_count - 1 && close(pipefd[1]) < 0)
			error(CLOSE_FAIL_ERRNO);
		if (i > 0 && close(precedent_fd) < 0)
			error(CLOSE_FAIL_ERRNO);
		if (i != cmds_count - 1)
			precedent_fd = pipefd[0];
		i++;
	}
	if (close(pipefd[0]) < 0)
		error(CLOSE_FAIL_ERRNO);
	return (wait_children(cpids, cmds_count));
}

int	exec_block(t_block *input, t_context *context)
{
	int	exit_value;

	if (input->op == NO_OP)
		return (exec_cmd(input->start, input->len, context));
	else if (input->op == PP)
		return (exec_pipe(input, context));
	else if (input->op == OR)
	{
		exit_value = exec_block(input->left, context);
		if (exit_value)
			return (exec_block(input->right, context));
		return (exit_value);
	}
	else if (input->op == AND)
	{
		exit_value = exec_block(input->left, context);
		if (!exit_value)
			return (exec_block(input->right, context));
		return (exit_value);
	}
	write(STDERR_FILENO, "Can't execute a bloc with undefined operator\n", 45);
	exit(GENERIC_ERRNO);
}
