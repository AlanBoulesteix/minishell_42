/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulest <aboulest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 11:13:39 by aboulest          #+#    #+#             */
/*   Updated: 2023/06/29 16:54:54 by aboulest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	skip(char *str, int *i)
{
	const char	c = str[*i];

	(*i)++;
	while (str[*i] != c)
		(*i)++;
	(*i)++;
}

void	reverse_skip(char *str, int *i)
{
	const char	c = str[*i];

	(*i)--;
	while (str[*i] != c)
		(*i)--;
	(*i)--;
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
			reverse_skip(str, &i);
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
