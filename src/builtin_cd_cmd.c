
#include "minishell.h"

int	cd_cmd(char **args, t_context *context, int input_fd, int output_fd)
{
	(void)input_fd;
	(void)output_fd;
	if (!args[0])
		return (cd(NULL, context));
	if (args[1])
		return (
			printf_fd(STDERR_FILENO, "minishell: cd: too many arguments\n"), 1);
	return (cd(args[0], context));
}
