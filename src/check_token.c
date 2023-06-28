/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlepille <vlepille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 17:49:34 by aboulest          #+#    #+#             */
/*   Updated: 2023/06/20 17:30:17 by vlepille         ###   ########.fr       */
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

int	type_token(char *str, int *i)
{
	*i += is_token(&str[*i]);
	return (OPE);
}

int	type_paren_open(int *i)
{
	(*i)++;
	return (PAREN_OPEN);
}

int	type_paren_close(int *i)
{
	(*i)++;
	return (PAREN_CLOSED);
}

int	type_redir(char *str, int *i)
{
	(*i) += is_redir(&str[*i]);
	return (REDIR);
}

int	type_word_quotes(char *str, int *i)
{
	char	c;

	c = str[*i];
	(*i)++;
	while (str[*i] && str[*i] != c)
		(*i)++;
	(*i)++;
	return (WORD);
}

int	type_word_or_newline(char *str, int *i)
{
	bool	in_simple;
	bool	in_double;

	in_simple = false;
	in_double = false;
	if (!str[*i])
		return (NEWLINE);
	while ((str[*i] && !is_token(&str[*i]) && !is_redir(&str[*i]) \
			&& str[*i] != ' ' && \
			str[*i] != '(' && str[*i] != ')' ) || (in_simple || in_double))
	{
		if (str[*i] == '\'' && !in_double)
			in_simple = !in_simple;
		if (str[*i] == '\"' && !in_simple)
			in_double = !in_double;
		(*i)++;
	}
	return (WORD);
}

int	find_type(char *str, int *i)
{
	if (is_token(&str[*i]))
		return (type_token(str, i));
	else if (str[*i] == '(')
		return (type_paren_open(i));
	else if (str[*i] == ')')
		return (type_paren_close(i));
	else if (is_redir(&str[*i]))
		return (type_redir(str, i));
	else if (str[*i] == '\'' || str[*i] == '\"')
		return (type_word_quotes(str, i));
	else
		return (type_word_or_newline(str, i));
}

int	find_next_type(char *str, int *i)
{
	int	j;

	while (str[*i] && str[*i] == ' ')
			(*i)++;
	j = *i;
	return (find_type(str, &j));
}

void	set_expected(int type, int *expected)
{
	if (type == WORD)
		*expected = WORD | OPE | REDIR | PAREN_CLOSED | NEWLINE;
	else if (type == OPE)
		*expected = WORD | REDIR | PAREN_OPEN;
	else if (type == PAREN_OPEN)
		*expected = WORD | REDIR | PAREN_OPEN;
	else if (type == PAREN_CLOSED)
		*expected = WORD | REDIR | PAREN_CLOSED | NEWLINE | OPE;
	else if (type == REDIR)
		*expected = WORD;
}

int	check_error(char *str)
{
	int	i;
	int	type;
	int	next_type;
	int	expected;

	i = 0;
	type = find_type(str, &i);
	expected = WORD | REDIR | PAREN_OPEN;
	if (!(type & expected))
		return (-1);
	i = 0;
	while (str[i])
	{
		type = find_type(str, &i);
		set_expected(type, &expected);
		next_type = find_next_type(str, &i);
		if (!(next_type & expected))
			return (i);
		if (!str[i])
			break ;
	}
	return (0);
}
