/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulest <aboulest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 15:31:01 by aboulest          #+#    #+#             */
/*   Updated: 2023/07/04 15:32:21 by aboulest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_db_tab(char **tab)
{
	int	i;

	i = -1;
	while (tab[++i])
		free(tab[i]);
	if (tab)
		free(tab);
}

char	**ft_path(t_env *env)
{
	char	*path;
	char	**final_path;

	path = get_env_value(env, "PATH");
	final_path = ft_split(path, ':');
	free_node(path);
	return (final_path);
}
