/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expend_default_utils2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulest <aboulest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 16:36:09 by aboulest          #+#    #+#             */
/*   Updated: 2023/07/04 16:37:37 by aboulest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	def_bool_and_incr_count(int *in_space, int *count)
{
	*in_space = 0;
	(*count)++;
}

void	tokenize_new_token(int *in_space, t_token *new_token, t_token *token)
{
	*in_space = 0;
	new_token->type = token->type;
	new_token->heredoc = token->heredoc;
	new_token->state = IGNORE;
	new_token->src = NULL;
}

void	free_slices(t_slice *slices)
{
	int	i;

	i = 0;
	while (slices[i].quote_type != END)
	{
		free_node(slices[i].str);
		i++;
	}
	free_node(slices);
}
