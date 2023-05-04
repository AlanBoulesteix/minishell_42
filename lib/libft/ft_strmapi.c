/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulest <aboulest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 09:29:26 by aboulest          #+#    #+#             */
/*   Updated: 2022/11/17 14:37:39 by aboulest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char				*mapi;
	unsigned int		i;

	i = 0;
	if (!s || !f)
		return (0);
	mapi = malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!mapi)
		return (0);
	while (s[i])
	{
		mapi[i] = f(i, s[i]);
		i++;
	}
	mapi[i] = '\0';
	return (mapi);
}

/*
char    ft_fonction(unsigned  int nb, char c)
{
	return (c + nb);
}

int main(void)
{
	char    *word;
	char	*str;
	void	*f;

	f = &ft_fonction;
	word = "bonjour";
	str = ft_strmapi(word, f);
	printf ("%s\n", str);	
	free(str);
	return (0);
}*/
