/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulest <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 11:13:39 by aboulest          #+#    #+#             */
/*   Updated: 2023/05/03 15:35:30 by aboulest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/readline.h>
#include <readline/history.h>

/*
INTEGRER LES () POUR DECOUPER LES BLOC A L'INTERIEUR DES PARANTHESES
EXECUTION DE GAUCHE A DROITE
CHECK DES $ ET TOKEN ENTRE CREATION BLOC ET EXECUSSION
*/

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
	t_list		*garb;
	garb = NULL;
	if (init_context(&context))
		return (1);
	while (!context.input || !ft_streq(context.input, "exit"))
	{
		context.input = readline("minishell$ ");
		add_history(context.input);

//////////////////////////////////////////////////////////////////////////////////////////
		//FUNCTION A DECOUPER
		t_block	input;
		input = (t_block){context.input, ft_strlen(context.input), UNDEFINE, NULL, NULL};
		// func
		get_blocks(&input, &garb);
			
			// @TODO verif only space
			// @TODO appel func(gauche)
			// @TODO appel func(droite)
			// printf("input: ");
			
			// put_block(input);
			// printf("input.gauche: ");
			// put_block(*input.gauche);
			// printf("input.droite: ");
			// put_block(*input.droite);

		
////////////////////////////////////////////////////////////////////////////////////////////////
	}
	free_all(&garb);
}
