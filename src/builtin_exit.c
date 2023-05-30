#include "minishell.h"
#include "libft.h"
#include <unistd.h>

int	exit_cmd(char **args, t_context *context, int input_fd, int output_fd)
{
	(void)context;
	(void)input_fd;
	(void)output_fd;
	if (args[0] && args[1])
		return (
			(write(STDERR_FILENO, "bash: exit: too many arguments\n", 31), 1));
	if (!args[0])
		exit(0);
	exit(ft_atoi(args[0]));
}
