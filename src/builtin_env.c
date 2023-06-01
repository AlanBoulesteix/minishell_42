#include "minishell.h"
#include <string.h>
#include <errno.h>

int	env_cmd(char **args, t_context *context, int input_fd, int output_fd)
{
	int	i;

	(void)input_fd;
	(void) args;
	i = 0;
	while (i < context->env.len)
	{
		if (printf_fd(output_fd, "%s\n", ((char **)context->env.tab)[i]) < 0)
		{
			printf_fd(STDERR_FILENO, "env: write error: %s\n", strerror(errno));
			return (125);
		}
		i++;
	}
	return (0);
}
