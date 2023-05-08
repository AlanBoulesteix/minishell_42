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

/*
   !!!!!!!!!!!!!! INTEGRER LES QUOTES POUR LES && || | !!!!!!!!!!!!!
   INTEGRER LES () POUR DECOUPER LES BLOC A L'INTERIEUR DES PARANTHESES
   EXECUTION DE GAUCHE A DROITE
   CHECK DES $ ET TOKEN ENTRE CREATION BLOC ET EXECUSSION
   */

void	print_double_tab(char **tab)
{
	int i;

	i = -1;
	while (tab[++i])
		printf("tab[%d]: %s\n", i, tab[i]);
}

int	main(void)
{
	t_context	context;
	t_list		*garb;
	t_block		input;
	char		**tab_block;

	garb = NULL;
	if (init_context(&context))
		return (1);
	while (!context.input || !ft_streq(context.input, "exit"))
	{
		context.input = readline("minishell$ ");
		add_history(context.input);

		//////////////////////////////////////////////////////////////////////////////////////////
		//FUNCTION A DECOUPER
		input = (t_block){context.input, ft_strlen(context.input), UNDEFINE, NULL, NULL};
		get_blocks(&input, &garb);


		tab_block = get_tab_block(&input, &garb);
		print_double_tab(tab_block);

		// @TODO verif only space
		// @TODO appel func(gauche)
		// @TODO appel func(droite)

		free_all(&garb);
		////////////////////////////////////////////////////////////////////////////////////////////////
	}
}
