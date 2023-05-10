#include "minishell.h"
#include "libft.h"
#include <unistd.h>

// @TODO take an arg
int	exit_cmd(char **args, t_context *context)
{
	(void)context;
	if (args[0] && args[1])
		return (
			(write(STDERR_FILENO, "bash: exit: too many arguments\n", 31), 1));
	if (!args[0])
		exit(0);
	exit(ft_atoi(args[0]));
}
