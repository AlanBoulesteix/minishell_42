/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_token_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulest <aboulest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 15:55:28 by vlepille          #+#    #+#             */
/*   Updated: 2023/07/05 13:05:36 by aboulest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	type_token(char *str, int *i);
int	type_paren_open(int *i);
int	type_paren_close(int *i);
int	type_redir(char *str, int *i);

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
			&& !is_space_tab(str[*i]) && \
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
