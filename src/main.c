/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlepille <vlepille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 11:13:39 by aboulest          #+#    #+#             */
/*   Updated: 2023/05/30 17:45:59 by vlepille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>

t_list	**_get_garbage();

/*WILDCARD ordre alphabetique et si identique minuscule en premier*/

int	main(int argc, char **argv, char **envp)
{
	t_context		context;
	t_block			main_block;
	char			*input;
	unsigned char	exit_value;
	int 			error_par;
	int				error_token;

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
		if (!input)
			exit((free_all(_get_garbage()), 0));
		add_history(input);

		error_par = check(input);
		error_token = check_error(input);
		if (error_par)
			print_error(error_par);
		else if (error_token)
			print_error_token(error_token, input);
		else
		{
			main_block = (t_block){input, ft_strlen(input), UNDEFINE, NULL, NULL};
			get_blocks(&main_block);
			exit_value = exec_block(&main_block, &context);
			// @TODO verif only space
			free_all(_get_garbage());
			free(input);
		}
	}
}
