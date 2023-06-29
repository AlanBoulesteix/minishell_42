#include "minishell.h"
#include <stdlib.h>

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
		[vector->len * vector->elem_size + i] = ((char *)elem)[i];
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
	ft_memmove(((char *)vector->tab) + ((offset + 1) * vector->elem_size),
		((char *)vector->tab) + (offset * vector->elem_size),
		(vector->len - offset) * vector->elem_size);
	i = -1;
	while (++i < vector->elem_size)
		((char *)vector->tab)[offset * vector->elem_size + i]
			= ((char *)elem)[i];
	vector->len++;
	return (0);
}