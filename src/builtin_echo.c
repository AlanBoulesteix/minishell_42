#include "minishell.h"

static int	option_newline(char *arg)
{
	int	i;

	if (!arg)
		return (1);
	if (arg[0] != '-')
		return (0);
	i = 1;
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	echo_cmd(char **args, t_context *context)
{
	int	opt_nl;

	(void)context;
	if (!*args)
		return (0);
	opt_nl = option_newline(*args);
	if (opt_nl)
		args++;
	while (*args)
	{
		printf("%s", *(args++));
		if (args[0])
			printf(" ");
	}
	if (!opt_nl)
		printf("\n");
	return (0);
}
