#include <sys/wait.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define test_error(arg) \
if (arg) \
{ \
	fprintf(stderr, "Line %d -> ", __LINE__); \
	perror(#arg); \
	exit(EXIT_FAILURE); \
}

typedef struct s_string
{
	char	*addr;
	int		len;
}	t_string;

#define NOT_FOUND -1
#define DEBUG 0
#define WITH_PARENTHESIS_FORK 0

int	has(char *str, int len, char *substr)
{
	int	parenthesis = 0;
	unsigned long j;

	for (int i = len - 1; i >= 0; i--)
	{
		if ((parenthesis += (str[i] == '(') - (str[i] == ')')) == 0)
		{
			for (j = 0; j < strlen(substr); j++)
			{
				if (str[i + j] != substr[j])
					break;
			}
			if (!substr[j])
				return (i);
		}
	}
	return (NOT_FOUND);
}

char	*concat(t_string cmd)
{
	char	*res = malloc(cmd.len + 1 + strlen("/bin/"));
	unsigned long		i;

	i = 0;
	while (i < strlen("/bin/"))
	{
		res[i] = "/bin/"[i];
		i++;
	}
	while (i < cmd.len + strlen("/bin/"))
	{
		res[i] = cmd.addr[i - strlen("/bin/")];
		i++;
	}
	res[i] = 0;
	return (res);
}

char	*str_to_charp(t_string str)
{
	char	*res = malloc(str.len + 1);
	unsigned long		i;

	if (str.len < 0)
		return (NULL);
	i = -1;
	while (++i < (unsigned long)str.len)
		res[i] = str.addr[i];
	res[i] = 0;
	return (res);
}

int	exec_cmd(char *str, int len, char *envp[])
{
	t_string	*current;
	t_string	cmd;
	t_string	arg;
	t_string	redir[2];
	int			in_redir = 0;
	int			word_start = -1;
	int			append;

	current = &cmd;
	arg.len = -1;
	redir[0].len = -1;
	redir[1].len = -1;
	for (int i = 0; i < len; i++)
	{
		if (word_start == -1 && str[i] != ' ')
		{
			if (str[i] == '>')
			{
				append = str[i + 1] == '>';
				in_redir = 2;
			}
			else if (str[i] == '<')
				in_redir = 1;
			else
				word_start = i;
		}
		if (word_start > -1 && (str[i] == ' ' || i + 1 == len))
		{
			if (in_redir == 1)
			{
				current = &redir[0];
				in_redir = 0;
			}
			else if (in_redir == 2)
			{
				current = &redir[2];
				in_redir = 0;
			}
			current->addr = str + word_start;
			current->len = i - word_start + (str[i] != ' ');
			current = &arg;
			word_start = -1;
		}
	}

	// not below if builtin
	char *path = concat(cmd);
	int	cpid;
	test_error((cpid = fork()) == -1);
	if (!cpid)
	{
		int	fd1, fd2;
		if (redir[0].len >= 0)
		{
			test_error((fd1 = open(str_to_charp(redir[0]), O_RDONLY)) == -1);
			dup2(fd1, STDIN_FILENO);
		}
		if (redir[0].len >= 0)
		{
			test_error((fd2 = open(str_to_charp(redir[0]), O_WRONLY | O_CREAT | (O_APPEND * append) | (O_TRUNC * !append), S_IRWXU | S_IRGRP | S_IXGRP | S_IXOTH)) == -1);
			dup2(fd2, STDOUT_FILENO);
		}
		if (DEBUG)
			printf("<%s><%s><%s>\n", path, str_to_charp(cmd), str_to_charp(arg));
		test_error((execve(path, (char *[]){str_to_charp(cmd), str_to_charp(arg), NULL}, envp)) == -1);
	}
	int	res;
	waitpid(cpid, &res, 0);
	return (res);
}

int	pip(char *str, int len, char *envp[])
{
	int	pipefd[2];
	int	cmds_len = 0;
	int	*cpids;
	int	precedent_fd;
	int	res;
	int	start = 0;
	int	j;

	for (int i = 0; i < len; i++)
		cmds_len += str[i] == '|';
	test_error(!(cpids = malloc(sizeof(int) * cmds_len)));
	test_error(pipe(pipefd) == -1)
	cpids[0] = fork();
	test_error(close(pipefd[0]) == -1);
	if (!cpids[0])
	{
		test_error(dup2(pipefd[1], STDOUT_FILENO) == -1);
		test_error(close(pipefd[1]) == -1);
		res = exec_cmd(str, has(str, len, "|"), envp);
	}
	test_error(close(pipefd[1]) == -1);
	precedent_fd = pipefd[0];
	j = 0;
	while ((start = has(str + start, len - start, "|") + 1) != -1)
	{
		j++;
		if (has(str + start, len - start, "|") != -1)
		{
			test_error(pipe(pipefd) == -1)
			cpids[j] = fork();
			if (!cpids[j])
			{
				test_error(dup2(precedent_fd, STDIN_FILENO) == -1);
				test_error(close(precedent_fd) == -1);
				test_error(dup2(pipefd[1], STDOUT_FILENO) == -1);
				test_error(close(pipefd[1]) == -1);
				res = exec_cmd(str + start, has(str + start, len - start, "|"), envp);
			}
			test_error(close(precedent_fd) == -1);
			test_error(close(pipefd[1]) == -1);
			precedent_fd = pipefd[0];
		}
		else
		{
			cpids[j] = fork();
			if (!cpids[j])
			{
				test_error(dup2(precedent_fd, STDIN_FILENO) == -1);
				test_error(close(precedent_fd) == -1);
				res = exec_cmd(str + start, len - start, envp);
			}
			test_error(close(precedent_fd) == -1);
		}
	}
	for (int i = 0; i < cmds_len; i++)
		waitpid(cpids[i], &res, 0);
	return (res);
}

int	exec_tree(char *str, int len, char *envp[])
{
	int		i;
	int		j;
	int		ret;

	if (DEBUG)
		printf("<%s> len = %d\n", str, len);
	i = 0;
	while (str[i] == ' ')
		i++;
	if (str[i] == '(')
	{
		j = len - 1;
		while (j > i)
		{
			if (str[j] == ')')
			{
				len = j - i - 1;
				break ;
			}
			j--;
		}
		str = str + i + 1;
		if (DEBUG)
			printf("Parenthesis<%s> len = %d\n", str, len);
		if (WITH_PARENTHESIS_FORK)
		{
			int cpid = fork();
			test_error(cpid == -1)
			if (!cpid)
				exit(exec_tree(str, len, envp));
			waitpid(cpid, &ret, 0);
			return (ret);
		}
		else
			return (exec_tree(str, len, envp));
	}
	if ((i = has(str, len, "&&")) != NOT_FOUND)
	{
		if ((ret = exec_tree(str, i, envp)) == EXIT_SUCCESS)
			return (exec_tree(str + i + 2, len - (i + 2), envp));
		return (ret);
	}
	if ((i = has(str, len, "||")) != NOT_FOUND)
	{
		if ((ret = exec_tree(str, i, envp)) != EXIT_SUCCESS)
			return (exec_tree(str + i + 2, len - (i + 2), envp));
		return (ret);
	}
	if (has(str, len, "|") != NOT_FOUND)
	{
		return (pip(str, len, envp));
	}
	return (exec_cmd(str, len, envp));
}

int	main(int argc, char *argv[], char *envp[])
{
	if (argc != 2)
		return (EXIT_FAILURE);

	return (exec_tree(argv[1], strlen(argv[1]), envp));
}
