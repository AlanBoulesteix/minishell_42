/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulest <aboulest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 17:10:43 by aboulest          #+#    #+#             */
/*   Updated: 2023/06/29 16:12:13 by aboulest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	count_and_switch(int *count, bool *in);
int		return_error_quotes(int count_double, int count_simple);
int		check_quotes(char *str);
int		check_paranthese(char *str);
int		quotes_error_handler(char *str, int *error, int mode);

int	check(char *str)
{
	int	error;
	int	i;

	i = 0;
	while (str[i] && (str[i] != '\'' || str[i] != '\"' || \
				str[i] != ')' || str[i] != '('))
		i++;
	if (str[i] != '\'' || str[i] != '\"')
	{
		if (quotes_error_handler(str, &error, 1))
			return (error);
	}
	if (str[i] != ')' || str[i] != '(')
	{
		if (quotes_error_handler(str, &error, 2))
			return (error);
	}
	return (0);
}
