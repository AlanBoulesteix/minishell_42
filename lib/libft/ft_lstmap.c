/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulest <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 19:04:44 by aboulest          #+#    #+#             */
/*   Updated: 2022/11/18 12:59:02 by aboulest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void*))
{
	t_list	*map;
	t_list	*elem;

	if (!lst || !f || !del)
		return (0);
	else
	{
		map = NULL;
		while (lst)
		{
			elem = ft_lstnew(f(lst->content));
			if (!elem)
			{
				ft_lstclear(&map, del);
				return (NULL);
			}
			ft_lstadd_back(&map, elem);
			lst = lst->next;
		}
		return (map);
	}
}

/*
void	ft_del(void *content)
{
	content = 0;
}

char	*ft_function(char *content)
{
	content = "101010";
	return (content);
}

int	main (void)
{
	t_list	*lst1;
	t_list	*lst2;
	t_list	*lst3;
	t_list	*result;
	void	*f;
	void	*d;
	
	lst1 = ft_lstnew("OUAIS OUAIS OUAIS");
	lst2 = ft_lstnew("NON NON NON");
	lst3 = ft_lstnew("AH LA ON EST BIEN");
	lst1->next = lst2;
	lst2->next = lst3;
	f = &ft_function;
	d = &ft_del;
	result = ft_lstmap(lst1, f, d);
	printf ("%d\n", ft_lstsize(lst1));
	printf ("%d\n", ft_lstsize(result));
	printf ("%s\n", (char *)lst1->content);
	printf ("%s\n", (char *)result->content);
	return (0);
}*/
