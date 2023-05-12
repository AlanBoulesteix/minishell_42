#include <sys/wait.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
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

typedef struct s_redir
{
	char	*arg;
	enum	{PIPE, STD_IO} type;
	char	append;
}	t_redir;

typedef struct s_cmd
{
	char	*path;
	char	**argv;
	char	**envp; // @TODO ? rm
	t_redir	in;
	t_redir	out;
}	t_cmd;

void	child(int pipefd[2], int precedent_fd, t_cmd cmds)
{
	int	fd;

	// INPUT REDIR
	if (cmds.in.arg)
	{
		test_error((fd = open(cmds.in.arg, O_RDONLY)) == -1);
		test_error(dup2(fd, STDIN_FILENO) == -1);
		test_error(close(fd) == -1);
	}
	else if (cmds.in.type == PIPE)
		test_error(dup2(precedent_fd, STDIN_FILENO) == -1);
	if (cmds.in.type == PIPE)
		test_error(close(precedent_fd) == -1);

	// OUTPUT REDIR
	if (cmds.out.arg)
	{
		test_error((fd = open(cmds.out.arg, O_WRONLY | O_CREAT | (O_APPEND * (cmds.out.append)) | (O_TRUNC * (!cmds.out.append)), S_IRWXU | S_IRGRP | S_IXGRP | S_IXOTH)) == -1);
		test_error(dup2(fd, STDOUT_FILENO) == -1);
		test_error(close(fd) == -1);
	}
	else if (cmds.out.type == PIPE)
		test_error(dup2(pipefd[1], STDOUT_FILENO) == -1);
	if (cmds.out.type == PIPE || cmds.in.type == PIPE)
		test_error(close(pipefd[1]) == -1);

	// execve
	test_error(execve(cmds.path, cmds.argv, cmds.envp) == -1);
}

int	main(int argc, char *argv[], char *envp[])
{
	int		pipefd[2] = {-1, -1};
	int		precedent_fd;
	t_cmd	*cmds;
	int		i;
	int		children_count = 4; // !!!!!!!!!!!!!!!!!!!!!!!!!
	int		*cpids;

	setbuf(stdout, NULL);
	(void)argc;
	(void)argv;

	test_error((cpids = malloc(sizeof(int) * children_count)) < 0);
	test_error((cmds = malloc(sizeof(t_cmd) * children_count)) < 0);
	int j = 0;
	cmds[j++] = (t_cmd){"/bin/ls", (char *[]){"ls", NULL}, envp, (t_redir){"infile", STD_IO, 0}, (t_redir){NULL, STD_IO, 0}};
	cmds[j++] = (t_cmd){"/bin/ls", (char *[]){"ls", NULL}, envp, (t_redir){"infile", STD_IO, 0}, (t_redir){NULL, PIPE, 0}};
	cmds[j++] = (t_cmd){"/bin/cat", (char *[]){"cat", NULL}, envp, (t_redir){NULL, PIPE, 0}, (t_redir){NULL, PIPE, 0}};
	cmds[j++] = (t_cmd){"/bin/wc", (char *[]){"wc", "-l", NULL}, envp, (t_redir){NULL, PIPE, 0}, (t_redir){"outfile", STD_IO, 1}};
	assert(j == children_count);

	i = 0;
	while (i < children_count)
	{
		if (cmds[i].in.type != PIPE)
			precedent_fd = -1;
		if (cmds[i].in.type == PIPE || cmds[i].out.type == PIPE)
			test_error(pipe(pipefd) == -1)
		cpids[i] = fork(); // @TODO in minishell : if builtin, don't fork if not in a pipe
		test_error(cpids[i] == -1)
		if (!cpids[i])
			child(pipefd, precedent_fd, cmds[i]);
		if (precedent_fd > 0)
			test_error(close(precedent_fd) == -1);
		if (cmds[i].in.type == PIPE || cmds[i].out.type == PIPE)
			test_error(close(pipefd[1]) == -1);
		precedent_fd = pipefd[0];
		i++;
	}
	if (precedent_fd > 0)
		test_error(close(precedent_fd) == -1);
	i = 0;
	while (i < children_count)
		wait(&cpids[i++]); // @TODO use waitpid
	free(cmds);
	free(cpids);
}
