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

unsigned char	exec_builtin(t_cmd cmd, t_context *context)
{
	const t_builtin_func	built_funcs[]
		= {echo_cmd, cd_cmd, pwd_cmd, export_cmd, unset_cmd, env_cmd, exit_cmd};
	const char				*built_str[] = {"echo", "cd", "pwd", "export", "unset", "env", "exit"};
	int						i;

	//if (cmd.input_fd >= 0 && dup2(STDIN_FILENO, 2000)) // @TODO change this system
	//	error(DUP2_FAIL_ERRNO, __LINE__);
	//if (cmd.output_fd >= 0 && dup2(STDOUT_FILENO, 2001))
	//	error(DUP2_FAIL_ERRNO, __LINE__);
	//if (cmd.input_fd >= 0 && dup2(cmd.input_fd, STDIN_FILENO))
	//	error(DUP2_FAIL_ERRNO, __LINE__);
	//if (cmd.output_fd >= 0 && dup2(cmd.output_fd, STDOUT_FILENO))
	//	error(DUP2_FAIL_ERRNO, __LINE__);

	//if (cmd.input_fd >= 0 && close(cmd.input_fd))
	//	error(CLOSE_FAIL_ERRNO, __LINE__);
	//if (cmd.output_fd >= 0 && close(cmd.output_fd))
	//	error(CLOSE_FAIL_ERRNO, __LINE__);
	//if (cmd.input_fd >= 0 && dup2(2000, STDIN_FILENO))
	//	error(DUP2_FAIL_ERRNO, __LINE__);
	//if (cmd.output_fd >= 0 && dup2(2001, STDOUT_FILENO))
	//	error(DUP2_FAIL_ERRNO, __LINE__);

	i = 0;
	while (i < 7)
	{
		if (ft_streq(cmd.cmd, built_str[i]))
			break ;
		i++;
	}
	if (i < 7)
		return (built_funcs[i](cmd.args + 1, context));
	else
		error_str("Command is not builtin <%s>\n", __LINE__);
	// @TODO free args and *args
	return (0);
}
