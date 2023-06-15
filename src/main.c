/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlepille <vlepille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 11:13:39 by aboulest          #+#    #+#             */
/*   Updated: 2023/06/14 18:37:50 by vlepille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/readline.h>
#include <readline/history.h>

t_list	**_get_garbage();

/*WILDCARD ordre alphabetique et si identique minuscule en premier*/

// function that return if char * is only space
int	is_only_space(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

int	main(int argc, char **argv, char **envp)
{
	t_context		context;
	t_block			main_block;
	char			*input;
	int				error_par;
	int				error_token;

	(void)argc;
	(void)argv;
	if (init_context(&context, envp))
		return (1);
	set_parent_signals();
	while (1)
	{
		context.stop = false;
		input = readline("minishell$ ");
		if (!input)
			exit((/*free_all(_get_garbage()), */0));
		if (is_only_space(input))
		{
			free(input);
			continue ;
		}
		add_history(input);

		error_par = check(input);
		error_token = check_error(input);
		if (error_par)
			print_error(error_par);
		else if (error_token)
			print_error_token(error_token, input);
		else
		{
			main_block = (t_block){input, NULL, NULL, ft_strlen(input), UNDEFINE};
			get_blocks(&main_block);
			exec_block(&main_block, &context);
			// @TODO verif only space
			//free_all(_get_garbage());
			free(input);
		}
	}
}
