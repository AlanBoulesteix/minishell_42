/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulest <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 11:59:42 by aboulest          #+#    #+#             */
/*   Updated: 2023/05/03 15:35:04 by aboulest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
##### MALLOC CHAINE ########
void	*my_malloc(size_t size, t_list **garbage);
void	free_all(t_list **garbage);
void	free_node(void *add, t_list **garbage)
*/

void	free_all(t_list **garbage)
{
	t_list	*tmp;

	while (*garbage)
	{
		tmp = (*garbage)->next;
		free((*garbage)->content);
		free(*garbage);
		*garbage = tmp;
	}
}

int	find_node_index(void *ptr, t_list **garbage)
{
	int		i;

	i = 0;
	while ((*garbage) && (*garbage)->content != ptr)
	{
		i++;
		*garbage = (*garbage)->next;
	}
	return (i);
}

void	free_node(void *add, t_list **garbage)
{
	t_list	*tmp;
	t_list	*node_free;
	int		i;
	int		j;

	tmp = *garbage;
	i = find_node_index(add, garbage);
	j = 0;
	while (++j < i)
	{
		if (j == i - 1)
		{
			node_free = tmp->next;
			if (tmp->next->next)
				tmp->next = tmp->next->next;
			else
				tmp->next = NULL;
			free(node_free->content);
			free(node_free);
		}
		tmp = tmp->next;
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
