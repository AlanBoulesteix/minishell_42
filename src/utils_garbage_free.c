/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_garbage_free.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlepille <vlepille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 17:04:02 by vlepille          #+#    #+#             */
/*   Updated: 2023/06/29 17:04:35 by vlepille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	**_get_garbage(void);

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

void	free_next_node(t_list *cpy)
{
	t_list	*tmp;

	tmp = cpy->next->next;
	free(cpy->next->content);
	free(cpy->next);
	cpy->next = tmp;
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
			return (free_next_node(cpy));
		cpy = cpy->next;
	}
	error_str("free_node: node not found", __LINE__, __FILE__);
}
