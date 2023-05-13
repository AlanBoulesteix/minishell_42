/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulest <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 11:13:39 by aboulest          #+#    #+#             */
/*   Updated: 2023/05/08 18:17:53 by aboulest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/readline.h>
#include <readline/history.h>

/*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	INTEGRER LES QUOTES POUR LES && || | 
	BLOCK DANS DES PARENTHESE ENVOYER DANS UN "SOUSHELL" AKA UN FORK
	CHECK DES $ ET TOKEN ENTRE CREATION BLOC ET EXECUSSION
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/

/*WILDCARD ordre alphabetique et si identique minuscule en premier*/

/*	EXPORT $VAR + ECHO MEME $VAR 
	SI PIPE $VAR PAS REMPLACER
	SINON $VAR REMPLACER
*/

void	print_double_tab(char **tab)
{
	int i;

	i = -1;
	while (tab[++i])
		printf("tab[%d]: {%s}\n", i, tab[i]);
}

void	print_op(t_block *input, int *op)
{
	int i;
	int nb_op;

	if (!op)
		printf("Y un seul block\n");
	i = -1;
	nb_op = count_block(input) - 1;
	while ( ++i < nb_op)
	{
		if (op[i] == AND)
			printf("op[%d]: AND\n", i + 1);
		if (op[i] == OR)
			printf("op[%d]: OR\n", i + 1);
		if (op[i] == PP)
			printf("op[%d]: PIPE\n", i + 1);
	}
}

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

int	check_token(char *str) // a REVOIR POUR LES QUOTES
{
	int 	i;
	bool	in_op;
	bool	in_simple;
	bool	in_double;

	i = 0;
	in_op = false;
	in_simple = false;
	in_double = false;
	while (str[i] && str[i] == ' ')
		i++;
	if (is_token(str + i))
		return (i);
	while (str[i])
	{
		if (str[i] == '\'' && !in_double)
			in_simple = true;
		if (str[i] == '\"' && !in_simple)
			in_double = true;
		while (in_op && (str[i] == ' ' || in_simple || in_double))
		{
			if (str[i] == '\'' && in_simple)
				in_simple = false;
			if (str[i] == '\"' && in_double)
				in_double = false;
			i++;
		}
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

int	main(void)
{
	t_context	context;
	t_list		*garb;
	t_block		input;

	garb = NULL;
	if (init_context(&context))
		return (1);
	while (!context.input || !ft_streq(context.input, "exit"))
	{
		context.input = readline("minishell$ ");
		add_history(context.input);

		//////////////////////////////////////////////////////////////////////////////////////////
		//FUNCTION A DECOUPER
		printf("la string %s renvoit %d\n", context.input, check_token(context.input));
		printf("------------------------------------------------------\n");

		int error = check(context.input);
		if (error)
			print_error_token(error);
		else
		{
			input = (t_block){context.input, ft_strlen(context.input), UNDEFINE, NULL, NULL};
			get_blocks(&input, &garb);

			char		**tab_block;
			int			*operation;

			tab_block = get_tab_block(&input, &garb);
			operation = get_op(&input, &garb);
			print_op(&input, operation);
			print_double_tab(tab_block);



			// @TODO verif only space
			// @TODO appel func(gauche)
			// @TODO appel func(droite)

			free_all(&garb);
		}
		////////////////////////////////////////////////////////////////////////////////////////////////
	}
}
