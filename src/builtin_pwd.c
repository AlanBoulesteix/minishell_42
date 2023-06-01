#include "minishell.h"
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

int	pwd_cmd(char **args, t_context *context, int input_fd, int output_fd)
{
	char	*cwd;

	(void)input_fd;
	(void)args;
	(void)context;
	cwd = getcwd(NULL, 0);
	if (!cwd)
		exit(MALLOC_FAIL_ERRNO);
	if (printf_fd(output_fd, "%s\n", cwd) < 0)
	{
		free(cwd);
		printf_fd(STDERR_FILENO, "minishell: pwd: %s\n", strerror(errno));
		return (1);
	}
	free(cwd);
	return (0);
}
