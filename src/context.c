#include "minishell.h"
#include "libft.h"

int	init_context(t_context *context, char **envp)
{
	char	*shlvl;

	init_env(&context->env, envp);
	init_vec(&context->export, sizeof(char *));
	context->exit = 0;
	context->pwd = getcwd(NULL, 0);
	if (!context->pwd)
		exit(MALLOC_FAIL_ERRNO);
	context->errno = add_env(&context->env, "PWD", context->pwd);
	if (context->errno)
		exit(context->errno);
	context->old_pwd = get_env_value(&context->env, "OLDPWD");
	if (!context->old_pwd)
	{
		context->errno = add_vec(&context->export, ft_strdup("OLDPWD"));
		if (context->errno)
			exit(context->errno);
	}
	shlvl = get_env_value(&context->env, "SHLVL");
	if (shlvl)
	{
		context->errno = add_env(&context->env, "SHLVL", ft_itoa(ft_atoi(shlvl) + 1)); // @TODO free itoa return
		if (context->errno)
			exit(context->errno);
	}
	else
	{
		context->errno = add_env(&context->env, "SHLVL", "1"); // @TODO verif bash int overflow behavior
		if (context->errno)
			exit(context->errno);
	}
	return (0);
}
