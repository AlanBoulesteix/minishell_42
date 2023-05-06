#include "minishell.h"
#include <stddef.h>

int	init_context(t_context *context, char **envp)
{
	context->exit = 0;
	init_env(&context->env, envp);
	init_vec(&context->export, sizeof(char *));
	return (0);
}
