/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlepille <vlepille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 12:19:28 by aboulest          #+#    #+#             */
/*   Updated: 2023/07/07 11:23:52 by vlepille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <errno.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

void	free_db_tab(char **tab);
char	**ft_path(t_env *env);

static char	*find_path_in_env(char *command, t_env *env)
{
	struct stat	buf;
	char		*final_path;
	char		**path;
	char		*add_slash;
	int			i;

	path = ft_path(env);
	if (!path)
		return (NULL);
	i = -1;
	while (path[++i])
	{
		add_slash = ft_strjoin(path[i], "/");
		if (!add_slash)
			return (free_db_tab(path), NULL);
		final_path = ft_strjoin(add_slash, command);
		free(add_slash);
		if (!final_path)
			return (free_db_tab(path), NULL);
		if (access(final_path, F_OK) == 0
			&& (!(stat(final_path, &buf) == 0 && S_ISDIR(buf.st_mode))))
			return (free_db_tab(path), final_path);
		free(final_path);
	}
	return (free_db_tab(path), NULL);
}

static char	*find_slash_path(char *command, t_context *context)
{
	struct stat	buf;

	if (stat(command, &buf) == 0 && S_ISDIR(buf.st_mode))
	{
		printf_fd(STDERR_FILENO, "minishell: %s: Is a directory\n", command);
		context->exit_value = 126;
		return (NULL);
	}
	if (access(command, X_OK) == 0)
		return (ft_strdup(command));
	else if (access(command, F_OK) == 0)
	{
		printf_fd(
			STDERR_FILENO, "minishell: %s: %s\n", command, strerror(errno));
		context->exit_value = 126;
		return (ft_strdup(command));
	}
	else
	{
		printf_fd(
			STDERR_FILENO, "minishell: %s: %s\n", command, strerror(errno));
		context->exit_value = 127;
		return (NULL);
	}
}

char	*find_path(char *command, t_context *context)
{
	if (command == NULL || command[0] == '\0')
		return (NULL);
	if (command[0] == '.' && !command[1])
	{
		printf_fd(STDERR_FILENO, "minishell: .: filename argument required\n");
		context->exit_value = 2;
		return (NULL);
	}
	if (ft_strchr(command, '/') != 0)
		return (find_slash_path(command, context));
	return (find_path_in_env(command, &context->env));
}
