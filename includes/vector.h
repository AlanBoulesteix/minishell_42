/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlepille <vlepille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 16:17:10 by vlepille          #+#    #+#             */
/*   Updated: 2023/06/29 16:17:11 by vlepille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

typedef struct s_vector
{
	void	*tab;
	int		elem_size;
	int		len;
	int		msize;
}	t_vector;

void	init_vec(t_vector *vector, int elem_size);
int		add_vec(t_vector *vector, void *elem);
		//__attribute__ ((warn_unused_result));
int		add_vec_offset(t_vector *vector, void *elem, int offset);
		//__attribute__ ((warn_unused_result));
void	join_vec(t_vector *vector, void *src, int len);
void	remove_vec(t_vector *vector, int offset);
void	destroy_vec(t_vector *vector);
void	print_vector(t_vector *vector, void (*print_func)(void *));

#endif
