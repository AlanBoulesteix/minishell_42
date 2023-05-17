/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlepille <vlepille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 11:13:39 by aboulest          #+#    #+#             */
/*   Updated: 2023/05/17 10:34:03 by vlepille         ###   ########.fr       */
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

int	main(int argc, char **argv, char **envp)
{
	t_context	context;
	t_block		main_block;
	char		*input;
	int			exit_value;

	(void)argc; // @TODO verif 0 arg
	(void)argv;
	if (init_context(&context, envp))
		return (1);
	while (1)
	{
		input = readline("minishell$ ");
		add_history(input);

		//////////////////////////////////////////////////////////////////////////////////////////
		//FUNCTION A DECOUPER

		int error_par = check(input);
		int error_token = check_error(input);
		if (error_par)
			print_error(error_par);
		else if (error_token)
			printf("Erreur parsing\n");
		else
		{
			main_block = (t_block){input, ft_strlen(input), UNDEFINE, NULL, NULL};
			get_blocks(&main_block, &context.garb);

			exit_value = exec_block(&main_block, &context);

			// char		**tab_block;
			// tab_block = get_tab_block(&input, &garb);
			// print_double_tab(tab_block);

			// @TODO verif only space
			// @TODO appel func(gauche)
			// @TODO appel func(droite)

			free_all(&context.garb);
			free(input);
		}
		////////////////////////////////////////////////////////////////////////////////////////////////
	}

}
