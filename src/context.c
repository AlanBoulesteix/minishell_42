#include "minishell.h"
#include "libft.h"

int	init_context(t_context *context, char **envp)
{
	char	*shlvl;

	init_env(&context->env, envp);
	init_vec(&context->export, sizeof(char *));
	context->exit = 0;
	add_export("PWD", context, 3);
	cd(".", context);
	add_export("OLDPWD", context, 6);
	shlvl = get_env_value(&context->env, "SHLVL");
	if (shlvl)
	{
		context->errno = add_env(&context->env, "SHLVL", ft_itoa(ft_atoi(shlvl) + 1)); // @TODO free itoa return
		if (context->errno)
			exit(context->errno);
	}
	else
		add_export("SHLVL=1", context, 5);
	return (0);
}
