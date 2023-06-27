/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulest <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 17:39:18 by aboulest          #+#    #+#             */
/*   Updated: 2023/05/15 17:24:19 by aboulest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_block	*init_left(t_block *input, char *str_block)
{
	t_block	*left;

	left = my_malloc(sizeof(struct s_block));
	left->start = input->start;
	left->len = (size_t)(str_block - input->start);
	left->left = NULL;
	left->right = NULL;
	return (left);
}

t_block	*init_right(t_block *input, char *str_block, char *op)
{
	t_block	*right;

	right = my_malloc(sizeof(struct s_block));
	right->start = str_block + ft_strlen(op);
	right->len = input->len - input->left->len - ft_strlen(op);
	right->left = NULL;
	right->right = NULL;
	return (right);
}

void	tree_rules(t_block *input, char *block, char *ope, t_context *context)
{
	if (ft_streq(ope, "&&"))
		input->op = AND;
	else if (ft_streq(ope, "||"))
		input->op = OR;
	else if (ft_streq(ope, "|"))
		input->op = PP;
	input->left = init_left(input, block);
	input->right = init_right(input, block, ope);
	get_blocks(input->left, context);
	get_blocks(input->right, context);
}

void	get_blocks(t_block *input, t_context *context)
{
	char	*str_block;

	str_block = last_operor(input->start, "&&", input->len);
	if (str_block)
		return (tree_rules(input, str_block, "&&", context));
	str_block = last_operor(input->start, "||", input->len);
	if (str_block)
		return (tree_rules(input, str_block, "||", context));
	str_block = last_operor(input->start, "|", input->len);
	if (str_block)
		return (tree_rules(input, str_block, "|", context));
	input->op = NO_OP;
	input->left = NULL;
	input->right = NULL;
	open_heredoc(input, context);
}