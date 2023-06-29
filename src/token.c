/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlepille <vlepille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 15:22:03 by vlepille          #+#    #+#             */
/*   Updated: 2023/06/29 15:44:29 by vlepille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	find_redir(char *str, int *index, int *type);
int		len_to_cpy(char *str);
char	*cpy_str(char *str, int *i, bool *in_simple, bool *in_double);
void	init_tok(t_token *token, int heredoc, char *str);
void	init_var_tok(int *i, int *j, bool *in_s, bool *in_d);

t_token	*tokenization(char *str, int nb_token, int heredoc)
{
	t_token *const	token = my_malloc(sizeof(t_token) * nb_token);
	int				i;
	int				j;
	bool			in_simple;
	bool			in_double;

	init_var_tok(&i, &j, &in_simple, &in_double);
	while (str[i])
	{
		while (str[i] && str[i] == ' ')
			i++;
		if (!str[i])
			break ;
		if (str[i] == '\'' && !in_double)
			in_simple = !in_simple;
		if (str[i] == '\"' && !in_simple)
			in_double = !in_double;
		if (is_redir(&str[i]) && !in_double && !in_simple)
			find_redir(&str[i], &i, &(token[j].type));
		else
			token[j].type = CMD;
		init_tok(&token[j], heredoc, cpy_str(str, &i, &in_simple, &in_double));
		j++;
	}
	return ((t_token *) token);
}
