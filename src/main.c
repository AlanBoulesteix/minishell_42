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

/*NEED TO IMPLENT GETBLOCK DONT FORGET TO FREE CHAR * FROM TRIM*/

void	free_tab(char **tab)
{
	int i;

	i = -1;
	while (tab[++i])
		free(tab[i]);
	free(tab);
}

int	nb_block(char *str)
{
	int i;
	int	count;

	i = -1;
	count = 1;
	while (str[++i])
	{
		if (str[i] == '|')
			count++;
	}
	return (count);
}

// char **get_bloc(char *str, t_list *garb)
// {
// 	char	**blocs;

// 	blocs = my_malloc(sizeof(char *) * (nb_block(str) + 1), garb);
	
// }

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
	

		printf("%d\n", nb_block(ft_strtrim(context.input, " \t\n")));
		
////////////////////////////////////////////////////////////////////////////////////////////////

	}
	free_all(&garb);
}
