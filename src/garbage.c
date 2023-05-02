/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulest <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 11:59:42 by aboulest          #+#    #+#             */
/*   Updated: 2023/05/02 14:24:29 by aboulest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_all(t_list **garbage)
{
	t_list *tmp;

	while (*garbage)
	{
		tmp = (*garbage)->next;
		free((*garbage)->content);
		free(*garbage);
		*garbage = tmp;
	}
}

void	*my_malloc(size_t size, t_list **garbage)
{
	void	*alloc;

	alloc = malloc(size);
	if (!alloc)
	{
		perror("Malloc");
		free_all(garbage);
		exit(EXIT_FAILURE);
	}
	ft_lstadd_back(garbage, ft_lstnew(alloc));
	return (alloc);
}
