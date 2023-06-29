/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlepille <vlepille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 17:49:34 by aboulest          #+#    #+#             */
/*   Updated: 2023/06/29 16:02:56 by vlepille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		is_token(char *str);
int		type_word_quotes(char *str, int *i);
int		type_word_or_newline(char *str, int *i);
int		find_type(char *str, int *i);
int		find_next_type(char *str, int *i);
void	set_expected(int type, int *expected);

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
