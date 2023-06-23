/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_garbage.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlepille <vlepille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 11:59:42 by aboulest          #+#    #+#             */
/*   Updated: 2023/06/23 02:49:12 by vlepille         ###   ########.fr       */
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

void	free_all(void)
{
	t_list **const	garbage = _get_garbage();
	t_list			*tmp;
	int				count;

	count = 0;
	while (*garbage)
	{
		count++;
		tmp = (*garbage)->next;
		free((*garbage)->content);
		free(*garbage);
		*garbage = tmp;
	}
	if (DEBUG)
		printf("free_all: %d nodes freed\n", count);
}

void	free_node(void *add)
{
	t_list **const	garbage = _get_garbage();
	t_list			*cpy;
	t_list			*node_free;

	if (!add)
		return ;
	if (!*garbage)
		error_str("free_node: garbage is empty", __LINE__, __FILE__);
	if ((*garbage)->content == add)
	{
		node_free = (*garbage)->next;
		free((*garbage)->content);
		free(*garbage);
		*garbage = node_free;
		return ;
	}
	cpy = *garbage;
	while (cpy->next)
	{
		if (cpy->next->content == add)
		{
			node_free = cpy->next->next;
			free(cpy->next->content);
			free(cpy->next);
			cpy->next = node_free;
			return ;
		}
		cpy = cpy->next;
	}
	error_str("free_node: node not found", __LINE__, __FILE__);
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
		//free_all(_get_garbage());
		exit(EXIT_FAILURE);
	}
	add_node(alloc);
	return (alloc);
}
