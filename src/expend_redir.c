#include "minishell.h"

int	is_ambigus(char *str)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (str[i])
	{
		while (str[i] && str[i] == ' ')
			i++;
		if (str[i])
			count++;
		while (str[i] && str[i] != ' ')
			i++;
	}
	return (count > 1);
}


int	expend_redir(t_token *tok, t_vector *tokens, int i, t_context *context)
{
	t_slice		*slices;

	slices = create_slices(tok->src);
	expend_vars(slices, context);
	if (is_ambigus(slices->str))
	{
		printf_fd(STDERR_FILENO,
						"minishell: %s : ambiguous redirect\n", ((t_token *)tokens->tab)[i].src);
		context->exit_value = 1;
		return (1);
	}
	else
		tok->f_str = slices->str;
	return (0);
}
