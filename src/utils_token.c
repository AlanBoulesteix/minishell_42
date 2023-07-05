/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulest <aboulest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 15:24:42 by vlepille          #+#    #+#             */
/*   Updated: 2023/07/05 15:39:37 by aboulest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// i_s for in_simple
// i_d for in_double
int	count_token(char *str)
{
	int		i;
	int		count;
	bool	i_s;
	bool	i_d;

	i = 0;
	count = 0;
	i_s = false;
	i_d = false;
	while (str[i])
	{
		while (is_sp(str[i]) || is_redir(&str[i]))
			i++;
		if (str[i])
			count ++;
		while (str[i] && ((!is_sp(str[i]) && !is_redir(&str[i])) || i_s || i_d))
		{
			if (str[i] == '\'' && !i_d)
				i_s = !i_s;
			if (str[i] == '\"' && !i_s)
				i_d = !i_d;
			i++;
		}
	}
	return (count);
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
