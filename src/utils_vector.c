#include "minishell.h"
#include <stdlib.h>

void	init_vec(t_vector *vector, int elem_size)
{
	vector->len = 0;
	vector->elem_size = elem_size;
	vector->msize = 0;
	vector->tab = NULL;
}

int	add_vec(t_vector *vector, void *elem)
{
	void	*new_tab;
	int		i;

	if (vector->len + 1 > vector->msize)
	{
		vector->msize = (vector->msize << 1) + !vector->msize;
		new_tab = my_malloc(vector->msize * vector->elem_size);
		i = -1;
		while (++i < vector->len * vector->elem_size)
			((char *)new_tab)[i] = ((char *)vector->tab)[i];
		free_node(vector->tab);
		vector->tab = new_tab;
	}
	i = -1;
	while (++i < vector->elem_size)
		((char *)vector->tab)
		[vector->len * vector->elem_size + i] = ((char *)&elem)[i];
	vector->len++;
	return (0);
}

int	add_vec_offset(t_vector *vector, void *elem, int offset)
{
	void	*new_tab;
	int		i;

	if (offset > vector->len)
		offset = vector->len;
	if (vector->len + 1 > vector->msize)
	{
		vector->msize = (vector->msize << 1) + !vector->msize;
		new_tab = my_malloc(vector->msize * vector->elem_size);
		i = -1;
		while (++i < vector->len * vector->elem_size)
			((char *)new_tab)[i] = ((char *)vector->tab)[i];
		free_node(vector->tab);
		vector->tab = new_tab;
	}
	ft_memmove(vector->tab + ((offset + 1) * vector->elem_size), vector->tab
		+ (offset * vector->elem_size),
		(vector->len - offset) * vector->elem_size);
	i = -1;
	while (++i < vector->elem_size)
		((char *)vector->tab)[offset * vector->elem_size + i]
			= ((char *)&elem)[i];
	vector->len++;
	return (0);
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
