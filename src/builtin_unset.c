#include "minishell.h"
#include <stdlib.h>

void	unset(char *key, t_context *context, int flag)
{
	int	i;

	if (flag & ENV)
		remove_env(&context->env, key);
	if (!(flag & EXPORT))
		return ;
	i = 0;
	while (i < context->export.len)
	{
		if (ft_streq(((char **)context->export.tab)[i], key))
			break ;
		i++;
	}
	if (i < context->export.len)
	{
		free(((char **)context->export.tab)[i]);
		remove_vec(&context->export, i);
	}
}

int	ft_unset(char **args, t_context *context)
{
	while (*args)
	{
		unset(*args, context, ENV | EXPORT);
		args++;
	}
	return (0);
}
