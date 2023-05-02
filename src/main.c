/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulest <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 11:13:39 by aboulest          #+#    #+#             */
/*   Updated: 2023/05/02 17:02:24 by aboulest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/readline.h>
#include <readline/history.h>

void	free_tab(char **tab)
{
	int i;

	i = -1;
	while (tab[++i])
		free(tab[i]);
	free(tab);
}


int	main(void)
{
	t_context	context;
	char		**input;
	t_list		*garb;

	garb = NULL;
	if (init_context(&context))
		return (1);
	while (!context.input || !ft_streq(context.input, "exit"))
	{
		context.input = readline("minishell$ ");
		add_history(context.input);

		//FUNCTION A DECOUPER

		input = ft_split(context.input, ' ');

		int i = -1;
		t_token	*lst_token;
		lst_token = NULL;
		while (input[++i])
			token_addbck(&lst_token, init_token(input[i], &garb));
		free_tab(input);
		t_token *tmp;
		tmp = lst_token;
		while (lst_token)
		{
			if (lst_token->type == 0)
				printf("content: %s\t type: CMD\n", lst_token->content);
			else if (lst_token->type == 1)
				printf("content: %s\t type: OPT\n", lst_token->content);
			else if (lst_token->type == 2)
				printf("content: %s\t type: ARG\n", lst_token->content);
			else if (lst_token->type == 3)
				printf("content: %s\t type: FILEs\n", lst_token->content);
			else if (lst_token->type == 4)
				printf("content: %s\t type: REDIR\n", lst_token->content);
			else if (lst_token->type == 5)
				printf("content: %s\t type: PIPE\n", lst_token->content);
			lst_token = lst_token->next;
		}
	}
	free_all(&garb);
}
