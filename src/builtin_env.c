#include "minishell.h"

int	env_cmd(char **args, t_context *context, int input_fd, int output_fd)
{
	int	i;

	(void)input_fd;
	(void) args;
	i = 0;
	while (i < context->env.len)
	{
		printf_fd(output_fd, "%s\n", ((char **)context->env.tab)[i]);
		i++;
	}
	return (0);
}
