/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulest <aboulest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 16:56:50 by aboulest          #+#    #+#             */
/*   Updated: 2023/07/05 15:39:37 by aboulest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>
#include <errno.h>
#include <string.h>

extern int	g_sigint_received;

int	cpy_cmd(char *cmd, char **addr)
{
	char	*res;
	int		i;

	i = 0;
	while (cmd[i] && !is_sp(cmd[i]))
		i++;
	res = my_malloc((i + 1) * sizeof(char));
	if (!res)
		exit(MALLOC_FAIL_ERRNO);
	i = -1;
	while (cmd[++i] && !is_sp(cmd[i]))
		res[i] = cmd[i];
	res[i] = 0;
	*addr = res;
	return (i);
}

void	cmd_child(t_cmd cmd, char *path, t_context *context)
{
	set_children_signals();
	context->in_fork = true;
	if (cmd.input_fd > 2)
	{
		dup2(cmd.input_fd, STDIN_FILENO);
		close(cmd.input_fd);
	}
	if (cmd.output_fd > 2)
	{
		dup2(cmd.output_fd, STDOUT_FILENO);
		close(cmd.output_fd);
	}
	if ((execve(path, cmd.cmd, context->env.tab)) < 0)
		printf_fd(STDERR_FILENO, "minishell: %s: %s\n", path, strerror(errno));
	exit(126);
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
			if (context->in_fork)
				exit(128 + SIGINT);
			else
				printf_fd(STDERR_FILENO, "\n");
		}
		else if (WTERMSIG(res) == SIGQUIT)
			printf_fd(STDERR_FILENO, "Quit (core dumped)\n");
	}
	else
		context->exit_value = 1;
	g_sigint_received = 0;
}

void	set_underscore_env(t_context *context, char **cmd)
{
	if (!*cmd)
		return ;
	while (*(cmd + 1))
		cmd++;
	add_env(&context->env, "_", *cmd);
}

void	exec_cmd(t_block *input, t_context *context)
{
	t_cmd	cmd;
	int		cpid;
	int		res;

	if (init_commande(&cmd, input, context))
		return ;
	if (cmd.input_fd < 0 || cmd.output_fd < 0)
		return ((void)(context->exit_value = 1));
	set_underscore_env(context, cmd.cmd);
	if (!cmd.path)
		context->exit_value
			= exec_builtin(cmd, context, cmd.output_fd, cmd.input_fd);
	else
	{
		cpid = fork();
		if (cpid < 0)
			error(FORK_FAIL_ERRNO, __LINE__, __FILE__);
		if (!cpid)
			cmd_child(cmd, cmd.path, context);
		close_fd(&cmd);
		set_basic_wait_signals();
		waitpid(cpid, &res, 0);
		set_basic_signals();
		child_exit_status(res, context);
	}
}
