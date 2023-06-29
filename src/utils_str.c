/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlepille <vlepille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 15:16:40 by vlepille          #+#    #+#             */
/*   Updated: 2023/06/29 15:16:41 by vlepille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int	ft_streq(const char *str1, const char *str2)
{
	int	i;

	i = 0;
	if (!str1)
		return (!str2);
	if (!str2)
		return (0);
	while (str1[i])
	{
		if (str1[i] != str2[i])
			return (0);
		i++;
	}
	return (!str2[i]);
}

int	ft_lineeq(const char *str1, const char *str2)
{
	int	i;

	i = 0;
	while (str1[i] && str1[1] != '\n')
	{
		if (str1[i] != str2[i])
			return (0);
		i++;
	}
	return (!str2[i] || str2[i] == '\n');
}

char	*ft_strnchr(const char *s, int n, int c)
{
	int	i;

	i = 0;
	while (s[i] && i < n)
	{
		if (s[i] == c)
			return ((char *)(s + i));
		i++;
	}
	return (NULL);
}
