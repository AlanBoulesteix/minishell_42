/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlepille <vlepille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 11:13:39 by aboulest          #+#    #+#             */
/*   Updated: 2023/05/30 15:32:27 by vlepille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>

t_list	**_get_garbage();

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
	t_context		context;
	t_block			main_block;
	char			*input;
	unsigned char	exit_value;

	(void)argc; // @TODO verif 0 arg
	(void)argv;
	if (init_context(&context, envp))
		return (1);
	if (signal(SIGINT, handle_sigint) == SIG_ERR)
		error(SIGNALS_FAIL_ERRNO, __LINE__);
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		error(SIGNALS_FAIL_ERRNO, __LINE__);
	while (1)
	{
		input = readline("minishell$ ");
		printf("input: {%s}\n", input);
		if (!input)
			exit(0); // @TODO free all
		add_history(input);

		//////////////////////////////////////////////////////////////////////////////////////////
		//FUNCTION A DECOUPER

		int error_par = check(input);
		int error_token = check_error(input);
		if (error_par)
		{
			print_error(error_par);
		}
		else if (error_token)
			print_error_token(error_token, context.input);
		else
		{
			main_block = (t_block){input, ft_strlen(input), UNDEFINE, NULL, NULL};
			get_blocks(&main_block);

			exit_value = exec_block(&main_block, &context);


			// char		**tab_block;
			// t_cmd		*cmd;
			// int i = -1;
			// tab_block = get_tab_block(&input);
			// while (tab_block[++i])
			// {
			// 	cmd = my_malloc(sizeof(t_cmd));
			// 	init_commande(cmd, tab_block[i], ft_strlen(tab_block[i]), &context.env);
			// 	printf("path = %s\n", cmd->path);
			// 	print_double_tab(cmd->cmd);
			// 	printf("input_fd: %d\n output_fd: %d\n", cmd->input_fd, cmd->output_fd);
			// 	printf("----------------------------------------------------------\n");
			// }

			// @TODO verif only space
			free_all(_get_garbage());
			free(input);
		}
		////////////////////////////////////////////////////////////////////////////////////////////////
	}
}
