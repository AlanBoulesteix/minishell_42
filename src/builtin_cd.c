#include "minishell.h"
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

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
	if (chdir(path))
		return (
			printf_fd(STDERR_FILENO,
				"minishell: cd: %s: %s\n", path, strerror(errno)), 1);
	free(context->oldpwd);
	context->oldpwd = context->pwd;
	if (is_in_export(context, "OLDPWD"))
	{
		unset("OLDPWD", context, EXPORT);
		if (get_env_offset(&context->env, "OLDPWD") >= 0)
			unset("OLDPWD", context, ENV);
		add_export("OLDPWD", context);
	}
	context->pwd = getcwd(NULL, 0);
	if (!context->pwd)
		exit(MALLOC_FAIL_ERRNO);
	if (is_in_export(context, "PWD"))
	{
		unset("PWD", context, EXPORT);
		add_env(&context->env, "PWD", context->pwd);
	}
	return (0);
}

int	cd_cmd(char **args, t_context *context, int input_fd, int output_fd)
{
	(void)input_fd;
	(void)output_fd;
	if (!args[0] || args[1])
		return (
			printf_fd(STDERR_FILENO, "minishell: cd: too many arguments\n"), 1);
	return (cd(args[0], context));
}
