/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulest <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 11:13:39 by aboulest          #+#    #+#             */
/*   Updated: 2023/05/15 17:40:13 by aboulest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	skip_quotes(char *str, int *i)
{
	bool	in_simple;
	bool	in_double;

	in_simple = false;
	in_double = false;
	if (str[*i] == '\'')
	{
		--(*i);
		while (*i > 0 && str[*i] != '\'')
			--(*i);
	}
	else if (str[*i] == '\"')
	{
		--(*i);
		while (*i > 0 && str[*i] != '\"')
			--(*i);
	}
	--(*i);
}

int	skip_parentheses(char *str, int *i)
{
	int		count;

	count = 1;
	while (--(*i) >= 0 && count)
		count += (str[*i] == ')') - (str[*i] == '(');
	if (count)
		return (1);
	return (0);
}

char	*last_operor(char *str, char *small, int len)
{
	int		i;
	int		j;

	i = len - 1;
	while (i >= 0)
	{
		if (str[i] == '\'' || str[i] == '\"')
			skip_quotes(str, &i);
		else if (str[i] == ')')
		{
			if (skip_parentheses(str, &i))
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
