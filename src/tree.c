/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulest <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 17:39:18 by aboulest          #+#    #+#             */
/*   Updated: 2023/05/08 18:01:20 by aboulest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*last_operor(char *str, char *small, int len)
{
	int		i;
	int		j;
	int		count;

	i = len - 1;
	if (!small)
		return (str);
	while (i >= 0)
	{
		if (str[i] == ')')
		{
			count = 1;
			while (--i >= 0 && count)
				count += (str[i] == ')') - (str[i] == '(');
			if (count)
				return (NULL);
		}
		else 
		{
			j = 0;
			while (str[i + j] && str[i + j] == small[j])
				j++;
			if (!small[j])
				return (str + i);
			i--;
		}
	}
	return (NULL);
}

t_block	*init_left(t_block *input, char *str_block, t_list **garb)
{
	t_block	*left;

	left = my_malloc(sizeof(struct s_block), garb);
	left->start = input->start;
	left->len = (size_t)(str_block - input->start);
	left->left = NULL;
	left->right = NULL;
	return (left);
}

t_block	*init_right(t_block *input, char *str_block, char *op, t_list **garb)
{
	t_block	*right;

	right = my_malloc(sizeof(struct s_block), garb);
	right->start = str_block + ft_strlen(op);
	right->len = input->len - input->left->len - ft_strlen(op);
	right->left = NULL;
	right->right = NULL;
	return (right);
}

void	tree_rules(t_block *input, char *block, char *ope, t_list **garb)
{
	if (ft_streq(ope, "&&"))
		input->op = AND;
	else if (ft_streq(ope, "||"))
		input->op = OR;
	else if (ft_streq(ope, "|"))
		input->op = PP;
	input->left = init_left(input, block, garb);
	input->right = init_right(input, block, ope, garb);
	get_blocks(input->left, garb);
	get_blocks(input->right, garb);
}

void	get_blocks(t_block *input, t_list **garb)
{
	char	*str_block;

	str_block = last_operor(input->start, "&&", input->len);
	if (str_block)
		return (tree_rules(input, str_block, "&&", garb));
	str_block = last_operor(input->start, "||", input->len);
	if (str_block)
		return (tree_rules(input, str_block, "||", garb));
	str_block = last_operor(input->start, "|", input->len);
	if (str_block)
		return (tree_rules(input, str_block, "|", garb));
	input->op = NO_OP;
	input->left = NULL;
	input->right = NULL;
}
/*
void	print_block(t_block *input)
{
	if (input && input->op != NO_OP)
	{
		print_block(input->left);
		print_block(input->right);
		return ;
	}
	else
	{
		put_block(*input);
		return ;
	}
}
*/
