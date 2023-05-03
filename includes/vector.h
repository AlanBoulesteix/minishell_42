#ifndef VECTOR_H
# define VECTOR_H

typedef struct s_vector
{
	void	*tab;
	int		elem_size;
	int		len;
	int		msize;
}	t_vector;

void	init_vector(t_vector *vector, int elem_size);
int		add_vector(t_vector *vector, void *elem)
		__attribute__ ((warn_unused_result));
void	destroy_vector(t_vector *vector);

#endif
