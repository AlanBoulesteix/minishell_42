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

void	child(int pipefd[2], int precedent_fd, t_cmd cmd)
{
	int	fd;

	// INPUT REDIR
	if (cmd.in.arg)
	{
		test_error((fd = open(cmd.in.arg, O_RDONLY)) == -1);
		test_error(dup2(fd, STDIN_FILENO) == -1);
		test_error(close(fd) == -1);
	}
	else if (cmd.in.type == PIPE)
		test_error(dup2(precedent_fd, STDIN_FILENO) == -1);
	if (cmd.in.type == PIPE)
		test_error(close(precedent_fd) == -1);

	// OUTPUT REDIR
	if (cmd.out.arg)
	{
		test_error((fd = open(cmd.out.arg, O_WRONLY | O_CREAT | (O_APPEND * (cmd.out.append)) | (O_TRUNC * (!cmd.out.append)), S_IRWXU | S_IRGRP | S_IXGRP | S_IXOTH)) == -1);
		test_error(dup2(fd, STDOUT_FILENO) == -1);
		test_error(close(fd) == -1);
	}
	else if (cmd.out.type == PIPE)
		test_error(dup2(pipefd[1], STDOUT_FILENO) == -1);
	if (cmd.out.type == PIPE)
		test_error(close(pipefd[1]) == -1);

	// execve
	test_error(execve(cmd.path, cmd.argv, cmd.envp) == -1);
}

void	exec(t_cmd	*cmds, int cmds_len)
{
	int		pipefd[2] = {-1, -1};
	int		precedent_fd;
	int		current_status;
	int		*cpids;
	int		i;
	int		j;

	test_error((cpids = malloc(sizeof(int) * cmds_len)) < 0);
	i = 0;
	while (i < cmds_len)
	{
		if ((*cmds).in.type != PIPE && (*cmds).out.type != PIPE)
		{
			cpids[i] = fork(); // @TODO in minishell : if builtin, don't fork
			test_error(cpids[i] == -1)
			if (!cpids[i])
				child((int [2]){-1, -1}, -1, *cmds);
			waitpid(cpids[i], &current_status, 0);
		}
		if ((*cmds).in.type != PIPE && (*cmds).out.type == PIPE)
		{
			j = i;
			test_error(pipe(pipefd) == -1)
			cpids[i] = fork();
			if (!cpids[i])
				child(pipefd, -1, (*cmds));
			test_error(close(pipefd[1]) == -1);
			precedent_fd = pipefd[0];
		}
		if ((*cmds).in.type == PIPE && (*cmds).out.type == PIPE)
		{
			test_error(pipe(pipefd) == -1)
			cpids[i] = fork();
			if (!cpids[i])
				child(pipefd, precedent_fd, (*cmds));
			test_error(close(precedent_fd) == -1);
			test_error(close(pipefd[1]) == -1);
			precedent_fd = pipefd[0];
		}
		if ((*cmds).in.type == PIPE && (*cmds).out.type != PIPE)
		{
			cpids[i] = fork();
			if (!cpids[i])
				child((int [2]){-1, -1}, precedent_fd, (*cmds));
			test_error(close(precedent_fd) == -1);
			while (j < i)
				waitpid(cpids[j++], &current_status, 0);
		}
		//if ((*cmds).in.type != PIPE)
		//	precedent_fd = -1;
		//if ((*cmds).in.type == PIPE || (*cmds).out.type == PIPE)
		//	test_error(pipe(pipefd) == -1)
		//cpids[i] = fork(); // @TODO in minishell : if builtin, don't fork if not in a pipe
		//test_error(cpids[i] == -1)
		//if (!cpids[i])
		//	child(pipefd, precedent_fd, (*cmds));
		//if ((*cmds).in.type == PIPE)
		//	test_error(close(precedent_fd) == -1);
		//if ((*cmds).in.type == PIPE || (*cmds).out.type == PIPE)
		//{
		//	test_error(close(pipefd[1]) == -1);
		//	precedent_fd = pipefd[0];
		//}
		cmds++;
		i++;
	}
	//i = 0;
	//while (i < cmds_len)
	//{
	//	waitpid(cpids[i++], &current_status, 0); // @TODO use waitpid
	//	//printf("cpid[%d] == %d -> %d\n", i - 1, cpids[i - 1], current_status);
	//}
	free(cpids);
}

int	first_test(char *envp[], char *infile, char *outfile)
{
	int		i;
	t_cmd	*cmds;
	int		cmds_len = 9; // !!!!!!!!!!!!!!!!!!!!!!!!!

	i = 0;
	test_error((cmds = malloc(sizeof(t_cmd) * cmds_len)) < 0);
	cmds[i++] = (t_cmd){"/bin/ls", (char *[]){"ls", NULL}, envp, (t_redir){infile, STD_IO, 0}, (t_redir){NULL, STD_IO, 0}};
	cmds[i++] = (t_cmd){"/bin/echo", (char *[]){"echo", "a", NULL}, envp, (t_redir){NULL, STD_IO, 0}, (t_redir){NULL, STD_IO, 0}};
	cmds[i++] = (t_cmd){"/bin/ls", (char *[]){"ls", NULL}, envp, (t_redir){infile, STD_IO, 0}, (t_redir){NULL, PIPE, 0}};
	cmds[i++] = (t_cmd){"/bin/cat", (char *[]){"cat", NULL}, envp, (t_redir){NULL, PIPE, 0}, (t_redir){NULL, PIPE, 0}};
	cmds[i++] = (t_cmd){"/bin/wc", (char *[]){"wc", "-l", NULL}, envp, (t_redir){NULL, PIPE, 0}, (t_redir){outfile, PIPE, 1}};
	cmds[i++] = (t_cmd){"/bin/grep", (char *[]){"grep", NULL}, envp, (t_redir){NULL, PIPE, 0}, (t_redir){NULL, STD_IO, 0}};
	cmds[i++] = (t_cmd){"/bin/echo", (char *[]){"echo", "b", NULL}, envp, (t_redir){NULL, STD_IO, 0}, (t_redir){NULL, STD_IO, 0}};
	cmds[i++] = (t_cmd){"/bin/echo", (char *[]){"echo", "c", NULL}, envp, (t_redir){NULL, STD_IO, 0}, (t_redir){NULL, PIPE, 0}};
	cmds[i++] = (t_cmd){"/bin/cat", (char *[]){"cat", NULL}, envp, (t_redir){NULL, PIPE, 0}, (t_redir){NULL, STD_IO, 0}};
	assert(i == cmds_len);

	exec(cmds, cmds_len);
	free(cmds);
	return (0);
}

int	second_test(char *envp[], char *infile, char *outfile)
{
	int		i;
	t_cmd	*cmds;
	int		cmds_len = 4; // !!!!!!!!!!!!!!!!!!!!!!!!!

	(void)infile;
	(void)outfile;
	i = 0;
	test_error((cmds = malloc(sizeof(t_cmd) * cmds_len)) < 0);
	cmds[i++] = (t_cmd){"/bin/ls", (char *[]){"ls", NULL}, envp, (t_redir){NULL, STD_IO, 0}, (t_redir){NULL, PIPE, 0}};
	cmds[i++] = (t_cmd){"/bin/cat", (char *[]){"cat", NULL}, envp, (t_redir){NULL, PIPE, 0}, (t_redir){NULL, PIPE, 0}};
	cmds[i++] = (t_cmd){"/bin/wc", (char *[]){"wc", "-l", NULL}, envp, (t_redir){NULL, PIPE, 0}, (t_redir){NULL, PIPE, 0}};
	cmds[i++] = (t_cmd){"/bin/grep", (char *[]){"grep", NULL}, envp, (t_redir){NULL, PIPE, 0}, (t_redir){NULL, STD_IO, 0}};
	assert(i == cmds_len);

	exec(cmds, cmds_len);
	free(cmds);
	return (0);
}

int	third_test(char *envp[], char *infile, char *outfile)
{
	int		i;
	t_cmd	*cmds;
	int		cmds_len = 4; // !!!!!!!!!!!!!!!!!!!!!!!!!

	(void)infile;
	(void)outfile;
	i = 0;
	test_error((cmds = malloc(sizeof(t_cmd) * cmds_len)) < 0);
	cmds[i++] = (t_cmd){"/bin/ls", (char *[]){"ls", NULL}, envp, (t_redir){NULL, STD_IO, 0}, (t_redir){NULL, PIPE, 0}};
	cmds[i++] = (t_cmd){"/bin/cat", (char *[]){"cat", NULL}, envp, (t_redir){NULL, PIPE, 0}, (t_redir){NULL, PIPE, 0}};
	cmds[i++] = (t_cmd){"/bin/grep", (char *[]){"grep", "e", NULL}, envp, (t_redir){NULL, PIPE, 0}, (t_redir){NULL, PIPE, 0}};
	cmds[i++] = (t_cmd){"/bin/wc", (char *[]){"wc", "-l", NULL}, envp, (t_redir){NULL, PIPE, 0}, (t_redir){NULL, STD_IO, 0}};
	assert(i == cmds_len);

	exec(cmds, cmds_len);
	free(cmds);
	return (0);
}

int	main(int argc, char *argv[], char *envp[])
{
	char	*infile;
	char	*outfile;
	int		test_num;

	//setbuf(stdout, NULL);
	if (argc < 3 || argc > 4)
	{
		infile = "infile";
		outfile = "outfile";
	}
	else
	{
		infile = argv[1];
		outfile = argv[2];
	}
	if (argc == 2)
		test_num = atoi(argv[1]);
	else if (argc == 4)
		test_num = atoi(argv[3]);
	else
		test_num = -1;

	if (test_num == -1 || test_num == 1)
		first_test(envp, infile, outfile);
	if (test_num == -1 || test_num == 2)
		second_test(envp, infile, outfile);
	if (test_num == -1 || test_num == 3)
		third_test(envp, infile, outfile);
}
