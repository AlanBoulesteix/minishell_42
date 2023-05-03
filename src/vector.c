#include "minishell.h"
#include <stdlib.h>

void	init_vector(t_vector *vector, int elem_size)
{
	vector->len = 0;
	vector->elem_size = elem_size;
	vector->msize = 0;
	vector->tab = NULL;
}

int	add_vector(t_vector *vector, void *elem)
{
	void	*new_tab;
	int		i;

	if (vector->len + 1 > vector->msize)
	{
		vector->msize = (vector->msize << 1) + !vector->msize;
		new_tab = malloc(vector->msize * vector->elem_size);
		if (!new_tab)
		{
			free(vector->tab);
			return (MALLOC_FAIL_ERRNO);
		}
		i = -1;
		while (++i < vector->len * vector->elem_size)
			((char *)new_tab)[i] = ((char *)vector->tab)[i];
		free(vector->tab);
		vector->tab = new_tab;
	}
	i = -1;
	while (++i < vector->elem_size)
		((char *)vector->tab)
		[vector->len * vector->elem_size + i] = ((char *)&elem)[i];
	vector->len++;
	return (0);
}

void	destroy_vector(t_vector *vector)
{
	if (vector->msize > 0)
		free(vector->tab);
}
