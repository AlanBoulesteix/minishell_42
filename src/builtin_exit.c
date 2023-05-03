#include "minishell.h"

int	ft_exit(char **args, t_context *context)
{
	(void)args;
	context->exit = 1;

	return (0);
}
