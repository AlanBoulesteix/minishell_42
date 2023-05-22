#include "minishell.h"
#include <unistd.h>
#include <stdlib.h>

int	is_in_export(t_context *context, char *key)
{
	int	i;

	if (get_env_offset(&context->env, key) != -1)
		return (1);
	i = 0;
	while (i < context->export.len)
	{
		if (ft_streq(((char **)context->export.tab)[i], key))
			return (1);
		i++;
	}
	return (0);
}

int	cd(char *path, t_context *context)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		exit(MALLOC_FAIL_ERRNO);
	if (is_in_export(context, "OLDPWD"))
	{
		unset("OLDPWD", context, EXPORT);
		add_env(&context->env, "OLDPWD", cwd);
	}
	if (chdir(path))
		return (perror("minishell"), 1);
	cwd = getcwd(NULL, 0);
	if (!cwd)
		exit(MALLOC_FAIL_ERRNO);
	if (is_in_export(context, "PWD"))
	{
		unset("PWD", context, EXPORT);
		add_env(&context->env, "PWD", cwd);
	}
	context->pwd_status = UPDATE_WITH_CWD;
	free(cwd);
	return (0);
}

int	cd_cmd(char **args, t_context *context)
{
	if (!args[0] || args[1])
		return ((write(STDERR_FILENO, "bash: cd: too many arguments\n", 29)), 1);
	return (cd(args[0], context));
}
