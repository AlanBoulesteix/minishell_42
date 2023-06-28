#include "minishell.h"

int	expend_redir(t_token *tok, t_vector *tokens, int i, t_context *context)
{
	t_slice		*slices;
	char		*src;
	slices = create_slices(tok->src);
	src = slices->str;
	expend_vars(slices, context);
	if (count_tokens_in_slices(slices) != 1)
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
