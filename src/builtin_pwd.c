#include "minishell.h"
#include <unistd.h>
#include <stdlib.h>

int	pwd_cmd(char **args, t_context *context, int input_fd, int output_fd)
{
	char	*cwd;

	(void)input_fd;
	(void)args;
	(void)context;
	cwd = getcwd(NULL, 0);
	if (!cwd)
		exit(MALLOC_FAIL_ERRNO);
	printf_fd(output_fd, "%s\n", cwd);
	free(cwd);
	return (0);
}
