/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulest <aboulest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 17:55:04 by aboulest          #+#    #+#             */
/*   Updated: 2022/11/18 12:15:47 by aboulest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_malloc_size(unsigned int start, size_t len, size_t strlen)
{
	char	*lemalloc;

	if (start > strlen)
	{
		lemalloc = malloc(1);
		lemalloc[0] = '\0';
		return (lemalloc);
	}
	else if (start + len > strlen)
		lemalloc = malloc(sizeof(char) * ((strlen - start) + 1));
	else
		lemalloc = malloc(sizeof(char) * (len + 1));
	return (lemalloc);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	j;
	char	*str;
	size_t	lenstr;

	lenstr = ft_strlen(s);
	str = ft_malloc_size(start, len, lenstr);
	if (!str)
		return (NULL);
	i = start;
	j = 0;
	while (i < lenstr && j < len)
	{
		str[j] = s[i];
		i++;
		j++;
	}
	str[j] = '\0';
	return (str);
}

/*
int	main(void)
{
	char	*s;
	size_t	len;
	unsigned int	start;

	start = 42;
	len = 42000000;
	s = ft_substr("tripouille", start, len);
	//printf("%s\n", ft_substr(s, start, len));
	if (!strcmp(s, ""))
		printf("YALA");
	else
		printf ("PUNAISE");
	return (0);
}
*/
