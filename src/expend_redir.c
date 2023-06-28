#include "minishell.h"

char	*tokenize_slices_redir(t_slice *slices)
{
	t_vector	current;
	int			i;

	init_vec(&current, sizeof(char));
	while (slices->quote_type != END)
	{
		i = 0;
		while (slices->str[i])
		{
			add_vec(&current, slices->str + i);
			i++;
		}
		slices++;
	}
	add_vec(&current, "");
	return (current.tab);
}

int	expend_redir(t_token *tok, t_vector *tokens, int i, t_context *context)
{
	t_slice		*slices;

	slices = create_slices(tok->src);
	expend_vars(slices, context);
	if (count_tokens_in_slices(slices) != 1)
	{
		printf_fd(STDERR_FILENO,
			"minishell: %s : ambiguous redirect\n", ((t_token *)tokens->tab)[i].src);
		context->exit_value = 1;
		return (1);
	}
	else
		tok->f_str = tokenize_slices_redir(slices);
	return (0);
}
