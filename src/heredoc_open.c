/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_open.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulest <aboulest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 15:01:43 by aboulest          #+#    #+#             */
/*   Updated: 2023/07/05 15:39:37 by aboulest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_sigint_received;

static int	is_metachar(char c)
{
	return (c == ' ' || c == '&' || c == '|' || c == '<'
		|| c == '>' || c == '\t');
}

static void	skip_parenthesis(char *str, int *i)
{
	int	parenthesis;

	parenthesis = 1;
	(*i)++;
	while (str[*i] && parenthesis)
	{
		if (str[*i] == '(')
			parenthesis++;
		else if (str[*i] == ')')
			parenthesis--;
		(*i)++;
	}
}

static void	heredoc_luncher(t_block *block, char *str, t_context *context)
{
	if (block->heredoc != -1)
		close_and_remove(block->heredoc, &context->fds_open);
	block->heredoc = heredoc((str), context);
}

static void	find_delimiter_and_lunch_heredoc(t_block *block,
	int *i, t_context *context)
{
	int		j;
	char	c;
	bool	in_simple;
	bool	in_double;

	j = -1;
	*i += 2;
	in_simple = false;
	in_double = false;
	while (is_sp(block->start[*i]))
		(*i)++;
	while (block->start[*i + (++j)] && (!is_metachar(block->start[*i + j])
			|| in_simple || in_double))
	{
		if (block->start[*i + j] == '\'' && !in_double)
			in_simple = !in_simple;
		if (block->start[*i + j] == '\"' && !in_simple)
			in_double = !in_double;
	}
	c = block->start[*i + j];
	block->start[*i + j] = 0;
	heredoc_luncher(block, (block->start) + *i, context);
	block->start[*i + j] = c;
	*i += j - 1;
}

void	open_heredoc(t_block *block, t_context *context)
{
	int		i;
	bool	in_simple;
	bool	in_double;

	i = 0;
	in_simple = false;
	in_double = false;
	while (i < block->len)
	{
		if (block->start[i] == '\'' && !in_double)
			in_simple = !in_simple;
		else if (block->start[i] == '\"' && !in_simple)
			in_double = !in_double;
		else if (!in_simple && !in_double && block->start[i] == '(')
		{
			skip_parenthesis(block->start, &i);
			continue ;
		}
		else if (block->start[i] == '<' && block->start[i + 1] == '<'
			&& !in_simple && !in_double)
			find_delimiter_and_lunch_heredoc(block, &i, context);
		if (g_sigint_received)
			return ;
		i++;
	}
}
