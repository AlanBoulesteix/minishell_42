
#import "minishell.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>
#include <readline/readline.h>

extern int	g_sigint_received;

char *join_line(char *s1, char *s2)
{
	int		len;
	int		i;
	int		j;
	char	*dup;

	len = ft_strlen(s1) + ft_strlen(s2);
	dup = my_malloc(sizeof(char) * (len + 2));
	i = 0;
	j = 0;
	while (s1 && s1[i])
	{
		dup[j] = s1[i];
		++j;
		++i;
	}
	i = 0;
	while (s2 && s2[i])
	{
		dup[j] = s2[i];
		++j;
		++i;
	}
	dup[j] = '\n';
	dup[j + 1] = '\0';
	return (dup);
}


char	*expend_quote(char *str)
{
	int		i;
	int		j;
	char	*res;
	bool	in_double;
	bool	in_simple;

	i = 0;
	j = 0;
	res = my_malloc(ft_strlen(str) * sizeof(char));
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

int	heredoc(char *str, t_context *context)
{
	int			pipefd[2];
	int			count;
	char		*line;
	char		*all_line;
	int			pid;
	int			res;

	str = expend_quote(str);
	line = NULL;
	all_line = NULL;
	count = 1;
	pipe(pipefd);
	pid = fork();
	if (pid == 0)
	{
		close(pipefd[0]);
		g_sigint_received = pipefd[1];
		set_heredoc_signal();
		while (!ft_streq(line, str))
		{
			free(line);
			line = readline("> ");
			if (!line)
			{
				printf_fd(STDERR_FILENO, "minishell: warning: here-document delimited by end-of-file (wanted `%s')\n", str);
				break ;
			}
			if (ft_streq(line, str))
				break ;
			else
			{
				all_line = join_line(all_line, line);
				free(line);
				line = NULL;
			}
		}
		write(pipefd[1], all_line, ft_strlen(all_line));
		close(pipefd[1]);
		exit(0);
	}
	set_wait_signals();
	close(pipefd[1]);
	waitpid(pid, &res, 0);
	set_parent_signals();
	child_exit_status(res, context);
	if (g_sigint_received)
		close(pipefd[0]); // @TODO
	free_node(str);
	return (pipefd[0]);
}