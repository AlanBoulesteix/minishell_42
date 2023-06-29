/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_token_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlepille <vlepille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 15:55:45 by vlepille          #+#    #+#             */
/*   Updated: 2023/06/29 15:56:52 by vlepille         ###   ########.fr       */
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
