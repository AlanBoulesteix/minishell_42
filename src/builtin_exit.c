#include "minishell.h"

// @TODO take an arg
int	exit_cmd(char **args, t_context *context)
{
	(void)args;
	context->exit = 1;

	return (0);
}
