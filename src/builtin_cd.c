#include "minishell.h"
#include <unistd.h>
#include <stdlib.h>

int	is_in_export(t_context *context, char *key)
{
	int	i;

	if (get_env_offset(&context->env, key))
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

int	ft_cd(char **args, t_context *context)
{
	if (chdir(args[0]))
		return ((write(STDERR_FILENO, "cd : can't cd in this path\n", 27)), 1); // @TODO modify error message according to real cd command
	free(context->old_pwd);
	context->old_pwd = context->pwd;
	context->pwd = getcwd(NULL, 0);
	if (is_in_export(context, "PWD"))
	{
		unset("PWD", context, EXPORT);
		context->errno = add_env(&context->env, "PWD", context->pwd);
		if (context->errno)
			exit(context->errno);
	}
	if (is_in_export(context, "OLDPWD"))
	{
		unset("PWD", context, EXPORT);
		context->errno = add_env(&context->env, "OLDPWD", context->old_pwd);
		if (context->errno)
			exit(context->errno);
	}
	if (!context->pwd)
		exit(MALLOC_FAIL_ERRNO);
	return (0);
}
