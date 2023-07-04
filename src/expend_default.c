/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expend_default.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulest <aboulest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 14:34:31 by aboulest          #+#    #+#             */
/*   Updated: 2023/07/04 16:36:33 by aboulest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	last_slice_empty(t_vector *current,
			int *in_space, t_token *new_tokens, t_token *token);
void	finish_token(int *in_space, t_vector *current, t_token *new_token);
int		is_in_token(int in_space, t_slice *slices, int i);
int		is_finish_token(int in_space, t_slice *slices, int i);
int		is_new_token(int in_space, t_slice *slices, int i);
void	def_bool_and_incr_count(int *in_space, int *count);
void	tokenize_new_token(int *in_space, t_token *new_token, t_token *token);
void	free_slices(t_slice *slices);

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
		j = 0;
		if (in_space && !slices[i].str[j] && slices[i].quote_type != NONE)
			def_bool_and_incr_count(&in_space, &count);
		while (slices[i].str[j])
		{
			if (slices[i].str[j] == ' ' && slices[i].quote_type == NONE)
				in_space = 1;
			else if (in_space)
				def_bool_and_incr_count(&in_space, &count);
			j++;
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
			if (is_new_token(in_space, slices, i))
				tokenize_new_token(&in_space, ++new_tokens, token);
			if (is_in_token(in_space, slices, i))
				add_vec(&current, slices->str + i);
			if (is_finish_token(in_space, slices, i))
				finish_token(&in_space, &current, new_tokens);
			i++;
		}
		if (!i && (slices + 1)->quote_type == END)
			last_slice_empty(&current, &in_space, new_tokens, token);
		slices++;
	}
}

char	*add_new_tokens_to_tokens(
	t_token *new_tokens, int len, t_vector *tokens, int i)
{
	int	j;

	if (len == 1)
	{
		((t_token *)tokens->tab)[i].f_str = new_tokens->f_str;
		free_node(new_tokens);
		return (((t_token *)tokens->tab)[i].f_str);
	}
	j = len - 1;
	while (j >= 0)
	{
		add_vec_offset(tokens, &new_tokens[j], i + 1);
		j--;
	}
	free_node(new_tokens);
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
	tokens_counter = count_tokens_in_slices(slices);
	if (!tokens_counter)
	{
		((t_token *)tokens->tab)[i].state = DEAD;
		return (my_malloc(1));
	}
	new_tokens = my_malloc(sizeof(t_token) * tokens_counter);
	tokenize_slices(slices, new_tokens, ((t_token *)tokens->tab) + i);
	free_slices(slices);
	return (add_new_tokens_to_tokens(new_tokens, tokens_counter, tokens, i));
}
