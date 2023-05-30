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

int	echo_cmd(char **args, t_context *context, int input_fd, int output_fd)
{
	int	opt_nl;

	(void)input_fd;
	(void)context;
	if (!*args)
		return (0);
	opt_nl = option_newline(*args);
	if (opt_nl)
		args++;
	while (*args)
	{
		printf_fd(output_fd, "%s", *(args++));
		if (args[0])
			printf_fd(output_fd, " ");
	}
	if (!opt_nl)
		printf_fd(output_fd, "\n");
	return (0);
}
