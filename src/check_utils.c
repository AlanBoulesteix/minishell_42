/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulest <aboulest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 16:11:11 by aboulest          #+#    #+#             */
/*   Updated: 2023/06/29 16:12:42 by aboulest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	count_and_switch(int *count, bool *in)
{
	(*count)++;
	*in = !(*in);
}

int	return_error_quotes(int count_double, int count_simple)
{
	if (count_double % 2)
		return (2);
	else if (count_simple % 2)
		return (3);
	else
		return (0);
}

int	check_quotes(char *str)
{
	int		i;
	int		count_simple;
	int		count_double;
	bool	in_simple;
	bool	in_double;

	i = 0;
	count_double = 0;
	count_simple = 0;
	in_simple = false;
	in_double = false;
	while (str[i])
	{
		while (str[i] && str[i] == ' ')
			i++;
		if (str[i] == '\"' && !in_simple)
			count_and_switch(&count_double, &in_double);
		else if (str[i] == '\'' && !in_double)
			count_and_switch(&count_simple, &in_simple);
		if (str[i])
			i++;
	}
	return (return_error_quotes(count_double, count_simple));
}

int	check_paranthese(char *str)
{
	int		i;
	bool	in_simple;
	bool	in_double;
	int		count;

	i = -1;
	count = 0;
	in_simple = false;
	in_double = false;
	while (str[++i])
	{
		if (str[i] == '\"' && in_simple == false)
			in_double = !in_double;
		if (str[i] == '\'' && in_double == false)
			in_simple = !in_simple;
		if ((str[i] == '(' || str[i] == ')') && \
				(in_simple == false && in_double == false))
			count += (str[i] == '(' ) - (str[i] == ')');
		if (count < 0)
			return (-4);
	}
	if (count > 0)
		return (4);
	return (0);
}

int	quotes_error_handler(char *str, int *error, int mode)
{
	if (mode == 1)
	{
		*error = check_quotes(str);
		if (*error != 0)
			return (1);
		*error = check_paranthese(str);
		if (error != 0)
			return (1);
	}
	else if (mode == 2)
	{
		*error = check_paranthese(str);
		if (*error != 0)
			return (1);
		*error = check_quotes(str);
		if (*error != 0)
			return (1);
	}
	return (0);
}
