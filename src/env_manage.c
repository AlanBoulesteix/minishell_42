/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_manage.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlepille <vlepille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 16:23:03 by vlepille          #+#    #+#             */
/*   Updated: 2023/07/06 18:12:16 by vlepille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdlib.h>
#include <stdio.h>

void	init_env(t_env *env, char **envp)
{
	char	*dup;

	init_vec(env, sizeof(char *));
	if (!envp)
		return ;
	while (*envp)
	{
		dup = ft_strdup(*(envp++));
		add_node(dup);
		add_env_full(env, dup);
	}
}

int	keyeq(char *key, char *envstr)
{
	int	i;

	i = 0;
	if (!envstr)
		return (0);
	while (key[i] && key[i] == envstr[i])
		i++;
	return (i * (envstr[i] == '=' && !key[i]));
}

char	*get_env_value(t_env *env, char *key)
{
	int		i;
	int		j;
	int		key_len;
	char	*res;

	i = -1;
	key_len = 0;
	while (++i < env->len && !key_len)
		key_len = keyeq(key, ((char **)env->tab)[i]);
	if (!key_len)
		return (NULL);
	res = my_malloc(ft_strlen(((char **)env->tab)[--i] + key_len + 1) + 1);
	j = -1;
	while (((char **)env->tab)[i][key_len + ++j + 1])
		res[j] = ((char **)env->tab)[i][key_len + j + 1];
	res[j] = 0;
	return (res);
}
