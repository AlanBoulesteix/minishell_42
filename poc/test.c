#include <sys/wait.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

void	child1(int pipefd[2], char *str, char *envp[])
{
	char	buf;

	(void)str;

	//close(pipefd[1]);	// close useless write
	//while (read(pipefd[0], &buf, 1) > 0)
	//	write(STDOUT_FILENO, &buf, 1);
	//write(STDOUT_FILENO, "\n", 1);
	//close(pipefd[0]);

	close(pipefd[0]);	// close useless read
	write(pipefd[1], str, strlen(str));
	close(pipefd[1]);	// put an EOF

	exit(EXIT_SUCCESS);
}

void	child2(int pipefd[2], char *str, char *envp[])
{
	char	buf;

	(void)str;

	//close(pipefd[0]);	// close useless read
	//write(pipefd[1], str, strlen(str));
	//close(pipefd[1]);	// put an EOF

	close(pipefd[1]);	// close useless write
	while (read(pipefd[0], &buf, 1) > 0)
		write(STDOUT_FILENO, &buf, 1);
	write(STDOUT_FILENO, "\n", 1);
	close(pipefd[0]);

	exit(EXIT_SUCCESS);
}

int	main(int argc, char *argv[], char *envp[])
{
	int		pipefd1[2];
	pid_t	cpid1;
	pid_t	cpid2;

	assert(argc == 2);

	if (pipe(pipefd1) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	cpid1 = fork();
	if (cpid1 == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (cpid1 == 0)
		child1(pipefd1, argv[1], envp);

	cpid2 = fork();
	if (cpid2 == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (cpid2 == 0)
		child2(pipefd1, argv[1], envp);
	close(pipefd1[0]);
	close(pipefd1[1]);
	wait(&cpid2);
	wait(&cpid1);
}
