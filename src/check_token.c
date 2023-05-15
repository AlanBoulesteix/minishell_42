/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulest <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 17:49:34 by aboulest          #+#    #+#             */
/*   Updated: 2023/05/15 17:49:48 by aboulest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_token(char *str)
{
	int	len;

	len = ft_strlen(str);
	if (len == 1 && str[0] == '|')
			return (1);		
	if (ft_strlen(str) < 2)
		return (0);
	if (str[0] == '&' && str[1] == '&')
		return (2);
	if (str[0] == '|' && str[1] == '|')
		return (2);
	if (str[0] == '|' && str[1] != '|')
		return (1);
	return (0);
}

void	skip_quotes(char *str, int *i)
{
	bool	in_simple;
	bool	in_double;

	in_simple = false;
	in_double = false;
	if (str[*i] == '\'' && in_double == false)
		in_simple = true;
	while (in_double && str[*i])
	{
		if (str[*i] == '\"')
			in_double = false;
		(*i)++;
	}
	if (str[*i] == '\"' && in_simple == false)
		in_double = true;
	while (in_simple && str[*i])
	{
		if (str[*i] == '\'')
			in_simple = false;
		(*i)++;
	}
}

int	check_token(char *str)
{
	int 	i;
	bool	in_op;

	i = 0;
	in_op = false;
	while (str[i] && str[i] == ' ')
		i++;
	if (is_token(str + i))
		return (i);
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			skip_quotes(str, &i);
		while (in_op && str[i] == ' ')
			i++;
		if (in_op && (is_token(str + i)))
			return (i);
		if(is_token(str + i))
		{
			in_op = true;
			i+= is_token(str + i);
			continue ;
		}
		if (in_op && str[i])
			in_op = false;
		i++;
	}
	return (in_op * -1);
}

int	print_error_token(int error, char *str)
{
	printf("minishell: syntax error near unexpected token `"); 
	if (error == -1)
		printf("newline\'\n");
	else
	{
		if (str[error] == '|' && str[error + 1] == '|')
			printf("||\'\n");
		else if (str[error] == '&')
			printf("&&\'\n");
		else if (str[error] == '|' && str[error + 1] != '|')
			printf("|\'\n");
	}
	return (2);
}