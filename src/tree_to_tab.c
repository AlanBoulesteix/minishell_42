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

char	*block_dup(t_block *input, t_list **garb)
{
	char	*block;
	int		i;

	i = -1;
	block = my_malloc(input->len + 1, garb);
	while (++i < input->len)
		block[i] = input->start[i];
	block[i] = '\0';
	return (block);
}

void	fill_tab_block(t_block *input, char **tab_block, int *i, t_list **garb)
{
	if (!input)
		return ;
	fill_tab_block(input->left, tab_block, i, garb);
	fill_tab_block(input->right, tab_block, i, garb);
	if (!(input->left) || !(input->right))
	{
		tab_block[*i] = block_dup(input, garb);
		(*i)++;
	}
}

char	**get_tab_block(t_block *input, t_list **garb)
{
	char	**tab_block;
	int		nb_block;
	int		index;

	index = 0;
	nb_block = count_block(input);
	tab_block = my_malloc(sizeof(char *) * (nb_block + 1), garb);
	fill_tab_block(input, tab_block, &index, garb);
	tab_block[nb_block] = NULL;
	return (tab_block);
}
