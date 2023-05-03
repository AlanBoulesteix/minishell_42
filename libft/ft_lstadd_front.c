/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulest <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 12:44:09 by aboulest          #+#    #+#             */
/*   Updated: 2022/11/23 17:32:24 by aboulest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (*lst)
		new->next = *lst;
	*lst = new;
}

/*int    main(void)
{
    char    tab1[] = "BABINKS";
    char    tab2[] = "IS A GOOD";
    char    tab3[] = "BABOY";
    t_list    *listtab1;
    t_list    *listtab2;
    t_list    *listtab3;

    listtab1 = ft_lstnew(tab1);
    listtab2 = ft_lstnew(tab2);
    listtab3 = ft_lstnew(tab3);
    ft_lstadd_front(&listtab2, listtab1);
    ft_lstadd_back(&listtab2, listtab3);
    printf("%s \n", (char *)listtab1->content);
    printf("%s \n", (char *)listtab1->next->content);
    printf("%s", (char *)listtab1->next->next->content);
    return (0);
}*/
