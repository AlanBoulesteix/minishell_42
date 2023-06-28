/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_to_tab.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulest <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 17:36:44 by aboulest          #+#    #+#             */
/*   Updated: 2023/05/08 17:38:22 by aboulest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_block(t_block *input)
{
	int	count;

	count = 0;
	if (input && input->op != NO_OP)
	{
		count += count_block(input->left);
		count += count_block(input->right);
		return (count);
	}
	else
	{
		count ++;
		return (count);
	}
}

void	fill_tab_block(t_block *input, t_block **tab_block, int *i)
{
	if (!input)
		return ;
	fill_tab_block(input->left, tab_block, i);
	fill_tab_block(input->right, tab_block, i);
	if (!(input->left) || !(input->right))
	{
		tab_block[*i] = input;
		(*i)++;
	}
}

t_block	**get_tab_block(t_block *input)
{
	t_block	**tab_block;
	int		nb_block;
	int		index;

	index = 0;
	nb_block = count_block(input);
	tab_block = my_malloc(sizeof(t_block *) * nb_block);
	fill_tab_block(input, tab_block, &index);
	return (tab_block);
}
