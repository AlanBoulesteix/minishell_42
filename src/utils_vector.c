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
