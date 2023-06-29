/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlepille <vlepille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 14:26:32 by vlepille          #+#    #+#             */
/*   Updated: 2023/06/29 14:33:41 by vlepille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_key(char *arg)
{
	int		i;
	char	*key;

	i = 0;
	while (arg[i] && arg[i] != '=')
		i++;
	key = ft_substr(arg, 0, i);
	add_node(key);
	return (key);
}

int	get_keylen(char *arg)
{
	int	len;

	len = 0;
	while (arg[len] && arg[len] != '=')
		len++;
	return (len);
}

int	valid(char *arg, int len)
{
	int	i;

	if (!len)
		return (0);
	if (arg[0] >= '0' && arg[0] <= '9')
		return (0);
	i = 0;
	while (i < len)
	{
		if (!((arg[i] >= '0' && arg[i] <= '9')
				|| (arg[i] >= 'A' && arg[i] <= 'Z')
				|| (arg[i] >= 'a' && arg[i] <= 'z')
				|| arg[i] == '_'))
			return (0);
		i++;
	}
	return (1);
}
