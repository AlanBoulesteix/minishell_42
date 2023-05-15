#include "minishell.h"

void	error(int errno)
{
	if (errno == MALLOC_FAIL_ERRNO)
		perror("Malloc");
	else if (errno == FORK_FAIL_ERRNO)
		perror("Fork");
	else if (errno == EXECVE_FAIL_ERRNO)
		perror("Execve");
	else if (errno == PIPE_FAIL_ERRNO)
		perror("Pipe");
	else if (errno == OPEN_FAIL_ERRNO)
		perror("Open");
	else if (errno == CLOSE_FAIL_ERRNO)
		perror("Close");
	else if (errno == DUP2_FAIL_ERRNO)
		perror("Close");
	else if (errno > 0)
		perror("Error handling not implementated yet");
	exit(errno);
}
