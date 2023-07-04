/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulest <aboulest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 15:22:44 by aboulest          #+#    #+#             */
/*   Updated: 2023/07/04 17:28:11 by aboulest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>
#include <readline/readline.h>

extern int	g_sigint_received;

static char	*expend_quote(char *str)
{
	int		i;
	int		j;
	char	*res;
	bool	in_double;
	bool	in_simple;

	i = 0;
	j = 0;
	res = my_malloc((ft_strlen(str) + 1) * sizeof(char));
	in_double = false;
	in_simple = false;
	while (str[i])
	{
		if (str[i] == '\'' && !in_double)
			in_simple = !in_simple;
		else if (str[i] == '\"' && !in_simple)
			in_double = !in_double;
		else
			res[j++] = str[i];
		i++;
	}
	res[j] = '\0';
	return (res);
}

static void	heredoc_child_process(int *pipefd, char *str, t_context *context)
{
	char	*all_line;

	close(pipefd[0]);
	g_sigint_received = pipefd[1];
	set_heredoc_signal();
	all_line = read_heredoc(str, context);
	write(pipefd[1], all_line, ft_strlen(all_line));
	close(pipefd[1]);
	close_fds_open(&context->fds_open);
	exit(0);
}

static void	heredoc_parent_process(
	int *pipefd, int pid, int *res, t_context *context)
{
	set_basic_wait_signals();
	close(pipefd[1]);
	waitpid(pid, res, 0);
	set_basic_signals();
	if (g_sigint_received)
	{
		child_exit_status(*res, context);
		close(pipefd[0]);
		g_sigint_received = 1;
	}
	else
		child_exit_status(*res, context);
	add_vec(&context->fds_open, &pipefd[0]);
}

int	heredoc(char *str, t_context *context)
{
	int			pipefd[2];
	int			pid;
	int			res;

	str = expend_quote(str);
	pipe(pipefd);
	pid = fork();
	if (pid < 0)
		error(FORK_FAIL_ERRNO, __LINE__, __FILE__);
	if (pid == 0)
		heredoc_child_process(pipefd, str, context);
	else
		heredoc_parent_process(pipefd, pid, &res, context);
	free_node(str);
	return (pipefd[0]);
}
