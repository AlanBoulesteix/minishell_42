#include "minishell.h"

int	ft_echo(char **args, t_context *context)
{
	(void)context;
	while (*args)
		printf("%s ", *(args++));
	printf("\n");
	return (0);
}
