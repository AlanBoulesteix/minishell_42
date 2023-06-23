#include "minishell.h"

int	get_slice_type(char c)
{
	if (c == '\'')
		return (SIMPLE);
	else if (c == '\"')
		return (DOUBLE);
	else
		return (NONE);
}

int	len_slice(char *src)
{
	const int	type = get_slice_type(*src);
	int			i;

	i = 0;
	src += (type == SIMPLE || type == DOUBLE);
	if (type == NONE)
	{
		while (src[i] && src[i] != '\'' && src[i] != '\"')
			i++;
	}
	else if (type == SIMPLE)
	{
		while (src[i] && src[i] != '\'')
			i++;
	}
	else
	{
		while (src[i] && src[i] != '\"')
			i++;
	}
	return (i);
}

void	copy_to_slice(t_slice *slice, char *src, int *i)
{
	int	j;

	slice->str = my_malloc((slice->len + 1) * sizeof(char));
	j = 0;
	*i += (slice->quote_type == SIMPLE || slice->quote_type == DOUBLE);
	while (j < slice->len)
	{
		slice->str[j] = src[*i];
		j++;
		(*i)++;
	}
	slice->str[j] = '\0';
}

t_slice	*create_slices(char *src)
{
	t_vector	slices;
	int			i;
	int			j;

	init_vec(&slices, sizeof(t_slice));
	i = 0;
	j = 0;
	while (src[i])
	{
		add_vec(&slices,
			&(t_slice){NULL, len_slice(src + i), get_slice_type(src[i])});
		copy_to_slice(&((t_slice *)slices.tab)[j], src, &i);
		i += (((t_slice *)slices.tab)[j].quote_type == SIMPLE
				|| ((t_slice *)slices.tab)[j].quote_type == DOUBLE);
		j++;
	}
	add_vec(&slices, &(t_slice){NULL, 0, END});
	return (slices.tab);
}

void	expend_slice(t_slice *slice, t_context *context)
{
	t_vector	res;
	int			i;

	if (slice->quote_type == SIMPLE)
		return ;
	init_vec(&res, sizeof(char));
	i = -1;
	while (slice->str[++i])
	{
		if (is_var(slice->str + i))
		{
			i += add_var(&res, slice->str + i, context) - 1;
		}
		else
			add_vec(&res, slice->str + i);
	}
	add_vec(&res, "");
	free_node(slice->str);
	slice->str = res.tab;
}

char	*expend_vars(t_slice *slices, t_context *context)
{
	t_vector	res;
	int			i;

	init_vec(&res, sizeof(char));
	i = 0;
	while (slices[i].quote_type != END)
	{
		expend_slice(&slices[i], context);
		i++;
	}
	return (res.tab);
}

int	count_tokens_in_slices(t_slice *slices)
{
	int	i;
	int	j;
	int	count;
	int	in_space;

	i = 0;
	count = 0;
	in_space = 1;
	while (slices[i].quote_type != END)
	{
		if (slices[i].quote_type == NONE)
		{
			j = 0;
			while (slices[i].str[j])
			{
				if (slices[i].str[j] == ' ')
					in_space = 1;
				else if (in_space && slices[i].str[j] != ' ')
				{
					in_space = 0;
					count++;
				}
				j++;
			}
		}
		i++;
	}
	return (count);
}

void	tokenize_slices(t_slice *slices, t_token *new_tokens, t_token *token)
{
	t_vector	current;
	int			in_space;
	int			i;

	init_vec(&current, sizeof(char));
	new_tokens--;
	in_space = 1;
	while (slices->quote_type != END)
	{
		i = 0;
		while (slices->str[i])
		{
			if (in_space && (slices->str[i] != ' ' || slices->quote_type != NONE))
			{
				in_space = 0;
				new_tokens++;
				new_tokens->type = token->type;
				new_tokens->heredoc = token->heredoc;
				new_tokens->state = IGNORE;
				new_tokens->src = NULL;
			}
			if (!in_space && (slices->str[i] != ' ' || slices->quote_type != NONE))
				add_vec(&current, slices->str + i);
			if ((!in_space && slices->str[i] == ' ' && slices->quote_type == NONE)
				|| (!slices->str[i + 1] && (slices + 1)->quote_type == END))
			{
				in_space = 1;
				add_vec(&current, "");
				new_tokens->f_str = current.tab;
				init_vec(&current, sizeof(char));
			}
			i++;
		}
		slices++;
	}
}

char	*add_new_tokens_to_tokens(
	t_token *new_tokens, int len, t_vector *tokens, int i)
{
	int	j;

	if (len == 1)
		return (((t_token *)tokens->tab)[i].f_str = new_tokens->f_str);
	j = len - 1;
	while (j >= 0)
	{
		add_vec_offset(tokens, &new_tokens[j], i + 1);
		j--;
	}
	((t_token *)tokens->tab)[i].state = DEAD;
	return (NULL);
}

char	*expend_default(char *src, t_vector *tokens, int i, t_context *context)
{
	t_token	*new_tokens;
	t_slice	*slices;
	int		tokens_counter;

	slices = create_slices(src);
	expend_vars(slices, context);
	for (int j = 0; slices[j].quote_type != END; j++)
		printf("slices: %s\n", slices[j].str);
	printf("count: %d\n", count_tokens_in_slices(slices));
	tokens_counter = count_tokens_in_slices(slices);
	if (!tokens_counter)
		return ("");
	new_tokens = my_malloc(sizeof(t_token) * tokens_counter);
	tokenize_slices(slices, new_tokens, ((t_token *)tokens->tab) + i);
	// // @TODO free slices (ptdr + content)
	// for (int j = 0; j < count_tokens_in_slices(slices); j++)
	// 	printf("new_tokens: %s\n", new_tokens[j].f_str);
	return (add_new_tokens_to_tokens(new_tokens, tokens_counter, tokens, i));
	// @TODO free new_tokens ptr
}
