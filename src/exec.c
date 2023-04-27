#include "minishell.h"
#include <stdio.h>

int	exec(t_command cmd, t_context *context)
{
	const t_builtin_func	built_funcs[]
		= {ft_echo, ft_cd, ft_pwd, ft_export, ft_unset, ft_env, ft_exit};
	const char				*built_str[] = {"echo", "cd", "pwd", "export", "unset", "env", "exit"};
	int						i;

	// DEV INFO
	printf("Command <%s>, Args <[", cmd.cmd);
	for (size_t j = 0; cmd.args[j]; j++)
	{
		printf("%s", cmd.args[j]);
		if (cmd.args[j + 1]) printf(", ");
	}
	printf("]>\n");
	// END DEV INFO
	i = 0;
	while (i < 7)
	{
		if (ft_lineeq(cmd.cmd, built_str[i]))
			return (built_funcs[i](cmd.args, context));
		i++;
	}
	printf("Command is not builtin <%s>\n", cmd.cmd);
	return (0);
}
