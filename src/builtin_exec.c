#include "minishell.h"
#include "libft.h"
#include <stdlib.h>

int	is_builtin(char *cmd)
{
	const char	*built_str[] = {"echo", "cd", "pwd", "export", "unset", "env", "exit"};
	int			i;

	i = 0;
	while (i < 7)
	{
		if (ft_streq(cmd, built_str[i]))
			return (1);
		i++;
	}
	return (0);
}

unsigned char	exec_builtin(t_cmd cmd, t_context *context, int output_fd, int input_fd)
{
	const t_builtin_func	built_funcs[]
		= {echo_cmd, cd_cmd, pwd_cmd, export_cmd, unset_cmd, env_cmd, exit_cmd};
	const char				*built_str[] = {"echo", "cd", "pwd", "export", "unset", "env", "exit"};
	int						i;

	i = 0;
	while (i < 7)
	{
		if (ft_streq(cmd.cmd, built_str[i]))
			break ;
		i++;
	}
	if (i < 7)
		return (built_funcs[i](cmd.args + 1, context, input_fd, output_fd));
	else
		error_str("Command is not builtin <%s>\n", __LINE__);
	// @TODO free args and *args
	return (0);
}
