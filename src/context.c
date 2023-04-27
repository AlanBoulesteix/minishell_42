#include "minishell.h"
#include <stddef.h>

int	init_context(t_context *context)
{
	context->exit = 0;
	return (0);
}
