/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_garbage.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlepille <vlepille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 11:59:42 by aboulest          #+#    #+#             */
/*   Updated: 2023/06/29 17:03:51 by vlepille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
##### MALLOC CHAINE ########
void	*my_malloc(size_t size, t_list **garbage);
void	free_all(t_list **garbage);
void	free_node(void *add, t_list **garbage)
*/

t_list	**_get_garbage(void)
{
	static t_list	*garbage;

	return (&garbage);
}

void	add_node_ignore_null(void *ptr)
{
	t_list	*new_node;

	if (!ptr)
		return ;
	new_node = ft_lstnew(ptr);
	if (!new_node)
	{
		perror("Malloc");
		free(ptr);
		exit(EXIT_FAILURE);
	}
	ft_lstadd_back(_get_garbage(), new_node);
}

void	add_node(void *ptr)
{
	t_list	*new_node;

	if (!ptr)
	{
		perror("Malloc");
		exit(EXIT_FAILURE);
	}
	new_node = ft_lstnew(ptr);
	if (!new_node)
	{
		perror("Malloc");
		free(ptr);
		exit(EXIT_FAILURE);
	}
	ft_lstadd_back(_get_garbage(), new_node);
}

void	*my_malloc(size_t size)
{
	void	*alloc;

	alloc = malloc(size);
	if (!alloc)
	{
		perror("Malloc");
		exit(EXIT_FAILURE);
	}
	add_node(alloc);
	return (alloc);
}
