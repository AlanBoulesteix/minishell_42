/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulest <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 11:13:39 by aboulest          #+#    #+#             */
/*   Updated: 2023/05/10 12:34:24 by aboulest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fill_op(t_block *input, int *ops, int *i)
{
	if (!(input->left) || !(input->right))
		return ;
	fill_op(input->left, ops, i);
	fill_op(input->right, ops, i);
	if (input->left && input->right)
	{
		ops[*i] = input->op;
		(*i)++;
	}
}

int	*get_op(t_block *input, t_list **garb)
{
	int		*ops;
	int		nb_block;
	int		index;

	nb_block = count_block(input);
	index = 0;
	if (nb_block == 1)
		return (NULL);
	ops = my_malloc(sizeof(int) * (nb_block - 1), garb);
	fill_op(input, ops, &index);
	return (ops);
}
