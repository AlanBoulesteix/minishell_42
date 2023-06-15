
#import "minishell.h"

char *join_line(char *s1, char *s2)
{
	int		len;
	int		i;
	int		j;
	char	*dup;

	len = ft_strlen(s1) + ft_strlen(s2);
	dup = my_malloc(sizeof(char) * (len + 1));
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
	dup[j] = '\0';
	return (dup);
}

int	ft_strcmp(char *s1, char *s2)
{
	int		i;
	int		end;

	i = 0;
	end = ft_strlen(s1) - 1;
	if(!s1 || !s2)
		return (1);
	s1[end] = '\0';
	while (s1[i])
	{
		if (s2[i] != s1[i])
		{
			s1[end] = '\n';
			return (1);
		}
		i++;
	}
	s1[end] = '\n';
	return (0);
}

int	heredoc(char *str)
{
	int			pipefd[2];
	int			count;
	char		*line;
	char *const	buf = (char [2]){0, 0};
	char		*all_line;

	line = NULL;
	all_line = NULL;
	count = 1;
	ft_bzero(buf, 2);
	pipe(pipefd);
	while (ft_strcmp(line, str))
	{
		while (count && buf[0] != '\n')
		{
			count = read(STDIN_FILENO, buf, 1);
			line = join_line(line, buf);
		}
		if (!ft_strcmp(line, str))
			break ;
		else
		{
			all_line = join_line(all_line, line);
			line = NULL;
			buf[0] = '\0';
		}
	}
	write(pipefd[1], all_line, ft_strlen(all_line));
	close(pipefd[1]);
	return (pipefd[0]);
}