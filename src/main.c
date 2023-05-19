/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlepille <vlepille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 11:13:39 by aboulest          #+#    #+#             */
/*   Updated: 2023/05/16 17:51:16 by vlepille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/readline.h>
#include <readline/history.h>

/*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	CHECK DES $ ET TOKEN ENTRE CREATION BLOC ET EXECUSSION
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/

/*WILDCARD ordre alphabetique et si identique minuscule en premier*/

/*	EXPORT $VAR + ECHO MEME $VAR
	SI PIPE $VAR PAS REMPLACER
	SINON $VAR REMPLACER
*/

void	print_double_tab(char **tab) //@TODO delete ?
{
	int i;

	i = -1;
	while (tab[++i])
		printf("tab[%d]: {%s}\n", i, tab[i]);
}



int	main(int argc, char **argv, char **envp)
{
	t_context	context;
	t_block		input;
	int			exit_value;

	(void)argc; // @TODO verif 0 arg
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
		else if (error_token)
			print_error_token(error_token, context.input);
		else
		{
			input = (t_block){context.input, ft_strlen(context.input), UNDEFINE, NULL, NULL};
			get_blocks(&input, &context.garb);
			exit_value = exec_block(&input, &context); // SEGFAULT STRING REMPLIT D'ESPACE OU VIDE

			// char		**tab_block;
			// t_cmd		*cmd;
			// int i = -1;
			// tab_block = get_tab_block(&input, &context.garb);
			// while (tab_block[++i])
			// {
			// 	cmd = malloc(sizeof(t_cmd));
			// 	init_commande(cmd, tab_block[i], ft_strlen(tab_block[i]), &context.garb, envp);
			// 	printf("path = %s\n", cmd->path);
			// 	print_double_tab(cmd->cmd);
			// 	printf("input_fd: %d\n output_fd: %d\n", cmd->input_fd, cmd->output_fd);
			// 	printf("----------------------------------------------------------\n");
			// 	free(cmd);
			//}
			// print_double_tab(tab_block); 

			// @TODO verif only space
			// @TODO appel func(gauche)
			// @TODO appel func(droite)
			free_all(&context.garb);
		}
		////////////////////////////////////////////////////////////////////////////////////////////////
	}

}
