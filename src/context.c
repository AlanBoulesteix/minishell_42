#include "minishell.h"
#include <stddef.h>

int	init_context(t_context *context)
{
	context->input = NULL;
	init_env(&context->env);
	return (0);
}
