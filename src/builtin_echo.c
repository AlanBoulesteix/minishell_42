#include "minishell.h"

int	echo_cmd(char **args, t_context *context)
{
	int	new_line;

	(void)context;
	new_line = (args[0] && !ft_streq(args[0], "-n"));
	if (!new_line)
		args++;
	while (*args)
	{
		printf("%s", *(args++));
		if (args[0])
			printf(" ");
	}
	if (new_line)
		printf("\n");
	return (0);
}
