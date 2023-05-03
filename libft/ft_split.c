/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulest <aboulest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 13:27:49 by aboulest          #+#    #+#             */
/*   Updated: 2022/11/21 18:11:28 by aboulest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_is_in(char s, char c)
{
	return (s == c);
}

static int	ft_nb_word(char const *s, char c)
{
	int	nb;

	nb = 0;
	while (*s)
	{
		while (*s && ft_is_in(*s, c))
			s++;
		if (*s && !ft_is_in(*s, c))
		{
			nb++;
			while (*s && !ft_is_in(*s, c))
				s++;
		}
	}
	return (nb);
}

static char	*ft_strdup_char(char const *s, char c)
{
	char	*dup;
	int		i;
	int		nb;

	nb = 0;
	i = 0;
	while (s[nb] && !ft_is_in(s[nb], c))
		nb++;
	dup = malloc (sizeof(char) * (nb + 1));
	if (!dup)
		return (NULL);
	while (i < nb)
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = 0;
	return (dup);
}

static void	ft_free(char **split, int index)
{
	while (index >= 0)
		free(split[index--]);
	free(split);
}

char	**ft_split(char const *s, char c)
{
	char		**split;
	int			j;
	int const	nb_word = ft_nb_word(s, c);

	j = -1;
	split = malloc (sizeof(char *) * (nb_word + 1));
	if (!split)
		return (NULL);
	while (++j < nb_word)
	{
		while (*s && ft_is_in(*s, c))
			s++;
		split[j] = ft_strdup_char(s, c);
		if (!split[j])
		{
			ft_free(split, j);
			return (NULL);
		}
		while (*s && !ft_is_in(*s, c))
			s++;
	}
	split[j] = 0;
	return (split);
}
/*
int    main(void)
{
    char            **split;
    unsigned int    i;

    i = 0;
    split = ft_split("Salut comment tu va ?", ' ');
    if (!split)
    {
        free(split);
        printf("NULL");
        return (0);
    }
    while (split[i])
    {
        printf("split[%d] = %s\n", i, split[i]);
        free(split[i]);
        i ++;
    }
    free(split);
*/
