/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulest <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 17:10:43 by aboulest          #+#    #+#             */
/*   Updated: 2023/05/10 17:10:58 by aboulest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_quotes(char *str)
{
	int 	i;
	int		count_simple;
	int 	count_double;
	bool	in_simple;
	bool	in_double;
	
	i = -1;
	count_double = 0;
	count_simple = 0;
	in_simple = false;
	in_double = false;
	while (str[++i])
	{
		while (str[i] && str[i]== ' ')
			i++;
		if (str[i] == '\"' || str[i] =='\'')
		{
			if (str[i] == '\"' && in_simple == false)
			{
				count_double ++;
				in_double = !in_double;
			}
			else if (str[i] == '\'' && in_double == false)
			{
				count_simple ++;
				in_simple = !in_simple;
			}
		}
	}
	if (count_double % 2)
		return (2);
	if (count_simple % 2)
		return (3);
	return (0);
}

int check_paranthese(char *str)
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
		if ((str[i] == '(' || str[i] == ')') && (in_simple ==false && in_double == false))
			count += (str[i] == '(' ) - (str[i] == ')');
	}
	if (count < 0)
		return (-4);
	else if (count > 0)
		return (4);
	return (0);
}

int	check(char *str)
{
	int error;
	int	i;

	i = 0;
	while (str[i] && (str[i] !='\'' || str[i] != '\"' || str[i] != ')' || str[i] != '('))
		i++;
	if (str[i] !='\'' || str[i] != '\"')
	{
		error = check_quotes(str);
		if (error != 0)
			return (error);
		error = check_paranthese(str);
		if (error != 0)
			return (error);
	}
	if (str[i] !=')' || str[i] != '(')
	{
		error = check_paranthese(str);
		if (error != 0)
			return (error);
		error = check_quotes(str);
		if (error != 0)
			return (error);
	}
	return (0);
}

int	print_error(int error)
{
	if (error == 2) 
		printf("minishell: syntax error near unexpected token `\"\'\n");
	else if (error == 3)
		printf("minishell: syntax error near unexpected token `\'\'\n");
	else if (error == 4)
		printf("minishell: syntax error near unexpected token `(\'\n");
	else if (error == -4)
		printf("minishell: syntax error near unexpected token `)\'\n");
	return (2);
}

// int main(int ac, char **av)
// {
// 	(void)ac;
// 	int		error;

// 	error = check(av[1]);
// 	if (error)
// 		print_error(error);
// 	else
// 		printf("SISI LA FAMILLE\n");
// }