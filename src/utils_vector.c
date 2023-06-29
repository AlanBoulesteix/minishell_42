/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_vector.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlepille <vlepille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 16:22:43 by vlepille          #+#    #+#             */
/*   Updated: 2023/06/29 16:22:44 by vlepille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

void	init_vec(t_vector *vector, int elem_size)
{
	vector->len = 0;
	vector->elem_size = elem_size;
	vector->msize = 0;
	vector->tab = NULL;
}

void	remove_vec(t_vector *vector, int offset)
{
	vector->len--;
	offset *= vector->elem_size;
	while (offset < vector->len * vector->elem_size)
	{
		((char *)vector->tab)[offset]
			= ((char *)vector->tab)[offset + vector->elem_size];
		offset++;
	}
}

void	destroy_vec(t_vector *vector)
{
	if (vector->msize > 0)
		free_node(vector->tab);
}

void	print_vector(t_vector *vector, void (*print_func)(void *))
{
	int	i;

	i = -1;
	printf_fd(STDOUT_FILENO, "[\n", vector->len);
	while (++i < vector->len)
	{
		printf_fd(STDOUT_FILENO, "\t");
		print_func(vector->tab + (i * vector->elem_size));
		if (i != vector->len - 1)
			printf_fd(STDOUT_FILENO, "\n");
	}
	printf_fd(STDOUT_FILENO, "\n]\n");
}

void	join_vec(t_vector *vector, void *src, int len)
{
	int	i;

	i = -1;
	while (++i < len)
		add_vec(vector, src + (i * vector->elem_size));
}
