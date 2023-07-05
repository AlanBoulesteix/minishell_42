/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expend_default_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulest <aboulest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 16:30:50 by aboulest          #+#    #+#             */
/*   Updated: 2023/07/05 14:31:21 by aboulest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	tokenize_new_token(int *in_space, t_token *new_token, t_token *token);

void	last_slice_empty(
	t_vector *current, int *in_space, t_token *new_tokens, t_token *token)
{
	if (*in_space)
		tokenize_new_token(in_space, ++new_tokens, token);
	add_vec(current, "");
	new_tokens->f_str = current->tab;
}

void	finish_token(int *in_space, t_vector *current, t_token *new_token)
{
	*in_space = 1;
	add_vec(current, "");
	new_token->f_str = current->tab;
	init_vec(current, sizeof(char));
}

int	is_new_token(int in_space, t_slice *slices, int i)
{
	return (in_space && (!is_space_tab(slices->str[i]) || slices->quote_type != NONE));
}

int	is_in_token(int in_space, t_slice *slices, int i)
{
	return (!in_space && (!is_space_tab(slices->str[i]) || slices->quote_type != NONE));
}

int	is_finish_token(int in_space, t_slice *slices, int i)
{
	return ((!in_space && is_space_tab(slices->str[i]) && slices->quote_type == NONE)
		|| (!slices->str[i + 1] && (slices + 1)->quote_type == END));
}
	