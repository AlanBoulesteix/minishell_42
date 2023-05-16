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
	IMPLEMENTER LES PARANTHESES ERREURS DINGUERIZE
	CHECKER SI TOUT EST OK DANS LES PARANTHESES
	IMPLEMENTER LES ERREURS REDIRECTIONS TYPE > < >>
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

// int	check_separator(char *str)
// {
// 	int i;
// 	bool in_redir;
// 	bool	in_op;

// 	i = -1;
// 	in_op = false;
// 	in_redir = false;
// 	while (str[++i])
// 	{
// 		if (str[i]  == '\'' || str[i] == '\"')
// 			skip_quotes(str, &i);
// 		if (str[i] == '(')
// 		{
// 			if (!in_op)
// 				return (1);
// 			if (in_redir)
// 				return (1);
// 		}
// 	}
// }

int	main(int argc, char **argv, char **envp)
{
	t_context	context;
	t_list		*garb;
	t_block		input;

	garb = NULL;
	(void)argc;
	(void)argv;
	if (init_context(&context, envp))
		return (1);
	while (!context.input || !ft_streq(context.input, "exit"))
	{
		context.input = readline("minishell$ ");
		add_history(context.input);

		//////////////////////////////////////////////////////////////////////////////////////////
		//FUNCTION A DECOUPER

		int error_par = check(context.input);
		int error_token = check_error(context.input);
		if (error_par)
			print_error(error_par);
		else if (error_token || context.input[0] == '&' || context.input[0] == '|')
			print_error_token(error_token, context.input);
		else
		{
			input = (t_block){context.input, ft_strlen(context.input), UNDEFINE, NULL, NULL};
			get_blocks(&input, &garb);

			char		**tab_block;
			tab_block = get_tab_block(&input, &garb);
			print_double_tab(tab_block);



			// @TODO verif only space
			// @TODO appel func(gauche)
			// @TODO appel func(droite)

		}
		////////////////////////////////////////////////////////////////////////////////////////////////
		free_all(&garb);
	}

}
