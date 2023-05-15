/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulest <aboulest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 19:33:39 by aboulest          #+#    #+#             */
/*   Updated: 2022/11/21 17:50:00 by aboulest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*cal;
	size_t	i;

	i = 0;
	if (size && (nmemb * size / size) != nmemb)
		return (0);
	cal = malloc(nmemb * size);
	if (!cal)
		return (0);
	while (i < nmemb * size)
	{
		((unsigned char *)cal)[i] = 0;
		i++;
	}
	return (cal);
}
