#include "minishell.h"
#include <unistd.h>
#include <stdlib.h>

int	ft_cd(char **args, t_context *context)
{
	(void)args;
	(void)context;
	if (chdir(args[0]))
		return ((write(STDERR_FILENO, "cd : can't cd in this path\n", 27)), 1);
	free(context->old_pwd);
	context->old_pwd = context->pwd;
	context->pwd = getcwd(NULL, 0);
	add_env(&context->env, "PWD", context->pwd);
	add_env(&context->env, "OLDPWD", context->old_pwd);
	if (!context->pwd)
		exit(MALLOC_FAIL_ERRNO);
	return (0);
}
