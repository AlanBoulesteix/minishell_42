#include "minishell.h"
#include "libft.h"

int	init_context(t_context *context, char **envp)
{
	int		ret;
	char	*shlvl;

	init_env(&context->env, envp);
	init_vec(&context->export, sizeof(char *));
	context->exit = 0;
	context->pwd = getcwd(NULL, 0);
	if (!context->pwd)
		exit(MALLOC_FAIL_ERRNO);
	add_env(&context->env, "PWD", context->pwd);
	context->old_pwd = get_env_value(&context->env, "OLDPWD");
	if (!context->old_pwd)
	{
		ret = add_vec(&context->export, ft_strdup("OLDPWD"));
		if (ret)
			exit(ret);
	}
	shlvl = get_env_value(&context->env, "SHLVL");
	if (shlvl)
	{
		add_env(&context->env, "SHLVL", ft_itoa(ft_atoi(shlvl) + 1)); // @TODO free itoa return
	}
	else
		add_env(&context->env, "SHLVL", "1");
	return (0);
}
