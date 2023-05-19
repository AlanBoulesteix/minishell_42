/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_path.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulest <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 12:19:28 by aboulest          #+#    #+#             */
/*   Updated: 2023/04/12 11:58:33 by aboulest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// @to do moddifier les mallocs !!

void	free_db_tab(char **tab)
{
	int	i;

	i = -1;
	while (tab[++i])
		free(tab[i]);
	if (tab)
		free(tab);
}

char	**ft_path(char **envp)
{
	char	*path;
	char	**final_path;
	int		i;

	i = -1;
	path = NULL;
	while (envp && envp[++i])
	{
		printf("env[%d]: %s\n", i, envp[i]);
		if (!ft_strncmp(envp[i], "PATH", 4))
			path = envp[i];
	}
	printf("env[%d]: %s\n", i, envp[i]);
	final_path = ft_split(path, ':');
	return (final_path);
}

char	*find_path_in_env(char *command, char **envp)
{
	char	*final_path;
	char	**path;
	char	*add_slash;
	int		i;

	path = ft_path(envp);
	if (!path)
		return (NULL);
	i = -1;
	while (path[++i])
	{
		add_slash = ft_strjoin(path[i], "/");
		final_path = ft_strjoin(add_slash, command);
		free(add_slash);
		if (access(final_path, F_OK) == 0)
			return (free_db_tab(path), final_path);
		if (final_path)
			free(final_path);
	}
	free_db_tab(path);
	return (NULL);
}

char	*find_path(char *command, char **envp)
{
	if (command == NULL)
		return (NULL);
	if (ft_strchr(command, '/') != 0)
	{
		if (access(command, X_OK) == 0)
			return (ft_strdup(command));
		else if (access(command, F_OK) == 0)
		{
			perror(command);
			return (ft_strdup(command));
		}
	}
	return (find_path_in_env(command, envp));
}
