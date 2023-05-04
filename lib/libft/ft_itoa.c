/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulest <aboulest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 14:52:59 by aboulest          #+#    #+#             */
/*   Updated: 2022/11/18 19:31:57 by aboulest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static int	ft_nb_chiffre(int n)
{
	int	count;

	if (n == 0)
		count = 1;
	else
	{
		count = (n < 0);
		while (n != 0)
		{
			count++;
			n = n / 10;
		}
	}
	return (count);
}

char	*ft_itoa(int n)
{
	int		nbchiffre;
	int		stop;
	char	*str;
	long	long_n;

	nbchiffre = ft_nb_chiffre(n);
	str = malloc(sizeof(char) * (nbchiffre) + 1);
	if (!str)
		return (NULL);
	stop = (n < 0);
	str[nbchiffre] = 0;
	if (stop)
		str[0] = '-';
	long_n = (n > 0) * (long) n - (n < 0) * (long)n;
	while (nbchiffre-- > stop)
	{
		str[nbchiffre] = long_n % 10 + '0';
		long_n = long_n / 10;
	}
	return (str);
}
