#include "minishell.h"

// @TODO ? if arg, print "env: invalid option"
int	env_cmd(char **args, t_context *context)
{
	int	i;

	(void) args;
	i = 0;
	while (i < context->env.len)
	{
		printf("%s\n", ((char **)context->env.tab)[i]);
		i++;
	}
	return (0);
}
