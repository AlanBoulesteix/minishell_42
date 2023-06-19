/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulest <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 17:49:34 by aboulest          #+#    #+#             */
/*   Updated: 2023/05/17 16:05:22 by aboulest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_token(char *str)
{
	int	len;

	len = ft_strlen(str);
	if (len == 1 && str[0] == '|')
		return (1);
	if (len < 2)
		return (0);
	if (str[0] == '&' && str[1] == '&')
		return (2);
	if (str[0] == '|' && str[1] == '|')
		return (2);
	if (str[0] == '|' && str[1] != '|')
		return (1);
	return (0);
}

int	is_redir(char *str)
{
	int	len;

	len = ft_strlen(str);
	if (len == 0)
		return (0);
	if (str[0] == '<' && str[1] != '<')
		return (1);
	if (str[0] == '<' && str[1] == '<')
		return (2);
	if (str[0] == '>' && str[1] != '>')
		return (1);
	if (str[0] == '>' && str[1] == '>')
		return (2);
	return (0);
}

int	find_type(char *str, int *i)
{
	char	c;

	if (is_token(&str[*i]))
	{
		*i += is_token(&str[*i]);
		return (OPE);
	}
	else if (str[*i] == '(')
	{
		(*i)++;
		return (PAREN_OPEN);
	}
	else if (str[*i] == ')')
	{
		(*i)++;
		return (PAREN_CLOSED);
	}
	else if (is_redir(&str[*i]))
	{
		(*i) += is_redir(&str[*i]);
		return (REDIR);
	}
	else if (str[*i] == '\'' || str[*i] == '\"')
	{
		c = str[*i];
		(*i)++;
		while (str[*i] && str[*i] != c)
			(*i)++;
		return (WORD);
	}
	else
	{
		if (!str[*i])
			return (NEWLINE);
		while (str[*i] && !is_token(&str[*i]) && !is_redir(&str[*i]) \
				&& str[*i] != ' ' && str[*i] != '(' && str[*i] != ')')
			(*i)++;
		return (WORD);
	}
}

int	find_next_type(char *str, int *i)
{
	int	j;
	while (str[*i] && str[*i] == ' ')
			(*i)++;
	j = *i;
	return (find_type(str, &j));
}

int	check_error(char *str)
{
	int	i;
	int	type;
	int	next_type;
	int	expected;

	i = 0;
	while (str[i])
	{
		type = find_type(str, &i);
		if (type == WORD)
			expected = WORD | OPE | REDIR | NEWLINE;
		else if (type == OPE)
			expected = WORD | REDIR | PAREN_OPEN;
		else if (type == PAREN_OPEN)
			expected = WORD | REDIR | PAREN_OPEN | PAREN_CLOSED;
		else if (type == PAREN_CLOSED)
			expected = WORD | REDIR | PAREN_CLOSED | NEWLINE;
		else if (type == REDIR)
			expected = WORD;
		next_type = find_next_type(str, &i);
		if (!(next_type & expected))
			return (i);
		if (!str[i])
			break ;
	}
	return (0);
}
