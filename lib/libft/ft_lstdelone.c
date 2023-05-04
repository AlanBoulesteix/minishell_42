/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulest <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 16:02:59 by aboulest          #+#    #+#             */
/*   Updated: 2022/11/17 14:44:27 by aboulest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void*))
{
	if (!del)
		return ;
	del(lst->content);
	free(lst);
}
/*
void	ft_del(void *content)
{
	content = 0;
}

int main (void)
{
	t_list *elem1;
	t_list *elem2;
	t_list *elem3;
	void	*del;

	del = &ft_del;
	elem1 = ft_lstnew("elem1");
	elem2 = ft_lstnew("elem2");
	elem1 = ft_lstnew("elem3");
	elem1->next = elem2;
	elem2->next = elem3;
	printf ("%d\n", ft_lstsize(elem1));
	ft_lstdelone(elem1, del);
	printf ("%d\n", ft_lstsize(elem1));
	return (0);
}*/
