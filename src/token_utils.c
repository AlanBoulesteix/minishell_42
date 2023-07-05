/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulest <aboulest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 15:43:47 by vlepille          #+#    #+#             */
/*   Updated: 2023/07/05 15:40:26 by aboulest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	find_redir(char *str, int *index, int *type)
{
	if (str[0] == '<' && str[1] != '<')
	{
		*type = REDIR_IN;
		(*index)++;
	}
	else if (str[0] == '<' && str[1] == '<')
	{
		*type = HERE_DOC;
		(*index) += 2;
	}
	else if (str[0] == '>' && str[1] != '>')
	{
		*type = REDIR_OUT;
		(*index)++;
	}
	else if (str[0] == '>' && str[1] == '>')
	{
		*type = REDIR_OUT_EXTEND;
		(*index) += 2;
	}
}

int	len_to_cpy(char *str)
{
	int		i;
	bool	in_simple;
	bool	in_double;

	i = 0;
	in_simple = false;
	in_double = false;
	while (str[i])
	{
		if (str[i] == '\'' && !in_double)
			in_simple = !in_simple;
		if (str[i] == '\"' && !in_simple)
			in_double = !in_double;
		if (is_redir(&str[i]) && !in_simple && !in_double)
			break ;
		if (is_sp(str[i]) && !in_simple && !in_double)
			break ;
		i++;
	}
	return (i);
}

char	*cpy_str(char *str, int *i, bool *in_simple, bool *in_double)
{
	char	*dup;
	int		len;
	int		j;

	while (is_sp(str[*i]))
		(*i)++;
	len = len_to_cpy(str + (*i));
	dup = my_malloc(sizeof(char) * (len +1));
	j = -1;
	while (++j < len)
	{
		if (str[*i] == '\'' && !(*in_double) && *in_simple)
			*in_simple = !(*in_simple);
		if (str[*i] == '\"' && !(*in_simple) && *in_double)
			*in_double = !(*in_double);
		dup[j] = str[*i];
		(*i)++;
	}
	dup[j] = '\0';
	return (dup);
}

void	init_tok(t_token *token, int heredoc, char *str)
{
	token->src = str;
	token->heredoc = heredoc;
	token->f_str = NULL;
	token->state = DEFAULT;
}

void	init_var_tok(int *i, int *j, bool *in_s, bool *in_d)
{
	*i = 0;
	*j = 0;
	*in_s = false;
	*in_d = false;
}
