#include "minishell.h"

void	print_error(char *str, int line)
{
	char	*l = ft_itoa(line); // @TODO use my_malloc

	write(STDERR_FILENO, "(line ", 6);
	write(STDERR_FILENO, l, ft_strlen(l));
	write(STDERR_FILENO, ") ", 2);
	free(l);
	perror(str);
}

void	error(int errno, int line)
{
	if (errno == MALLOC_FAIL_ERRNO)
		print_error("Malloc", line);
	else if (errno == FORK_FAIL_ERRNO)
		print_error("Fork", line);
	else if (errno == EXECVE_FAIL_ERRNO)
		print_error("Execve", line);
	else if (errno == PIPE_FAIL_ERRNO)
		print_error("Pipe", line);
	else if (errno == OPEN_FAIL_ERRNO)
		print_error("Open", line);
	else if (errno == CLOSE_FAIL_ERRNO)
		print_error("Close", line);
	else if (errno == DUP2_FAIL_ERRNO)
		print_error("Dup2", line);
	else if (errno > 0)
		print_error("Error handling not implementated yet", line);
	exit(errno);
}
