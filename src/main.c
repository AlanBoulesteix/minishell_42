/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulest <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 11:13:39 by aboulest          #+#    #+#             */
/*   Updated: 2023/05/01 16:02:59 by aboulest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/readline.h>
#include <readline/history.h>

/* ***************************/
/********** FUITE A GERER*****/
/**PLUS CHECKER SI C'EST OK***/
/*****************************/
/*****************************/

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
			token_addbck(&lst_token, init_token(input[i]));
		t_token *tmp;
		tmp = lst_token;
		while (lst_token)
		{
			printf("content: %s\t type: %d\n", lst_token->content, lst_token->type);
			lst_token = lst_token->next;
		}
	}
}
