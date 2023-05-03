/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulest <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 16:22:02 by aboulest          #+#    #+#             */
/*   Updated: 2022/11/18 12:47:39 by aboulest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*buffer;

	if (!lst || !del)
		return ;
	while (*lst)
	{
		buffer = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = buffer;
	}
}
/*
void	ft_del(void *content)
{
	content = 0;
}

int	main(void)
{
	t_list	*elem1 = ft_lstnew("elem1");
	t_list	*elem2 = ft_lstnew("elem2");
	t_list	*elem3 = ft_lstnew("elem3");
	t_list	*elem4 = ft_lstnew("elem4");
	void	*del;

	del = &ft_del;
	elem1->next = elem2;
	elem2->next = elem3;
	elem3->next = elem4;
	printf ("%s\n", (char *)elem1->next->content);
	ft_lstclear(&elem2, del);
	printf("%s\n", (char *)elem1->next->content);
	return (0);
}*/
