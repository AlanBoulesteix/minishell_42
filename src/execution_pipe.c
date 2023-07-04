/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_pipe.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulest <aboulest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 16:23:30 by aboulest          #+#    #+#             */
/*   Updated: 2023/07/04 16:25:37 by aboulest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <signal.h>
#include <sys/wait.h>

extern int	g_sigint_received;

static void	pipe_child(
	int pipefd[3], t_block *cmd,
	int pipe_place, t_context *context)
{
	context->in_fork = true;
	if (pipe_place != LAST_PIPE && close(pipefd[0]) < 0)
		error(CLOSE_FAIL_ERRNO, __LINE__, __FILE__);
	if (pipe_place != FIRST_PIPE && dup2(pipefd[2], STDIN_FILENO) < 0)
		error(DUP2_FAIL_ERRNO, __LINE__, __FILE__);
	if (pipe_place != FIRST_PIPE && close(pipefd[2]) < 0)
		error(CLOSE_FAIL_ERRNO, __LINE__, __FILE__);
	if (pipe_place != LAST_PIPE && dup2(pipefd[1], STDOUT_FILENO) < 0)
		error(DUP2_FAIL_ERRNO, __LINE__, __FILE__);
	if (pipe_place != LAST_PIPE && close(pipefd[1]) < 0)
		error(CLOSE_FAIL_ERRNO, __LINE__, __FILE__);
	close_fds_open_except(&context->fds_open, cmd->heredoc);
	exec_block(cmd, context);
	exit(context->exit_value);
}

void	child_pipe_exit_status(int res, t_context *context)
{
	if (WIFEXITED(res))
		context->exit_value = WEXITSTATUS(res);
	else if (WIFSIGNALED(res))
	{
		context->exit_value = 128 + WTERMSIG(res);
		if (WTERMSIG(res) == SIGINT)
			g_sigint_received = 1;
		else if (WTERMSIG(res) == SIGQUIT)
			printf_fd(STDERR_FILENO, "Quit (core dumped)\n");
	}
	else
		context->exit_value = 1;
}

static void	wait_children(int *cpids, const int cmds_count, t_context *context)
{
	int	exit_value;
	int	i;

	i = -1;
	set_basic_wait_signals();
	while (++i < cmds_count)
		waitpid(cpids[i], &exit_value, 0);
	set_basic_signals();
	child_pipe_exit_status(exit_value, context);
}

void	exec_pipe(t_block *input, t_context *cont)
{
	t_block *const	*cmds_tab = get_tab_block(input);
	const int		cmds_count = count_block(input);
	int *const		cpids = my_malloc(cmds_count * sizeof(int));
	int				pipefd[3];
	int				i;

	i = -1;
	while (++i < cmds_count)
	{
		if (i != cmds_count - 1 && pipe(pipefd) < 0)
			error(PIPE_FAIL_ERRNO, __LINE__, __FILE__);
		cpids[i] = fork();
		cpids[i] < 0 && error(FORK_FAIL_ERRNO, __LINE__, __FILE__);
		if (!cpids[i])
			pipe_child(pipefd, cmds_tab[i], (!!i) + (i == cmds_count -1), cont);
		if (cmds_tab[i]->heredoc != -1)
			close_and_remove(cmds_tab[i]->heredoc, &cont->fds_open);
		if (i != cmds_count - 1 && close(pipefd[1]) < 0)
			error(CLOSE_FAIL_ERRNO, __LINE__, __FILE__);
		if (i > 0 && close(pipefd[2]) < 0)
			error(CLOSE_FAIL_ERRNO, __LINE__, __FILE__);
		if (i != cmds_count - 1)
			pipefd[2] = pipefd[0];
	}
	wait_children(cpids, cmds_count, cont);
}
