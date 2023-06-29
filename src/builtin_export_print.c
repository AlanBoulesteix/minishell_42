/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_print.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlepille <vlepille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 14:26:37 by vlepille          #+#    #+#             */
/*   Updated: 2023/06/29 14:32:43 by vlepille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <errno.h>
#include <string.h>

static int	ft_keycmp(char *key1, char *key2)
{
	int	i;

	i = -1;
	while (key1[++i] && key1[i] != '=' && key2[i] != '=')
		if (key1[i] != key2[i])
			return (key1[i] - key2[i]);
	if (key1[i] == key2[i]
		|| (!key1[i] && key2[i] == '=') || (!key1[i] && key2[i] == '='))
		return (0);
	if (!key1[i] || key1[i] == '=')
		return (-1);
	if (key2[i] == '=')
		return (1);
	return (0);
}

static int	get_min(char **cpy_env, int len)
{
	int	i;
	int	min;

	i = -1;
	min = -1;
	while (++i < len)
		if (cpy_env[i]
			&& (min == -1 || ft_keycmp(cpy_env[min], cpy_env[i]) > 0))
			min = i;
	return (min);
}

static char	*get_value(char *arg)
{
	int		i;
	char	*value;

	i = 0;
	while (arg[i] && arg[i] != '=')
		i++;
	if (!arg[i])
		return (NULL);
	value = ft_substr(arg, i + 1, ft_strlen(arg) - i - 1);
	add_node(value);
	return (value);
}

static int	print_one(int output_fd, char *var)
{
	char	*key;
	char	*value;

	key = get_key(var);
	value = get_value(var);
	if ((value && printf_fd(output_fd, "declare -x %s=\"%s\"\n", key, value) < 0)
		|| (!value && printf_fd(output_fd, "declare -x %s\n", key) < 0))
	{
		free_node(key);
		free_node(value);
		printf_fd(STDERR_FILENO, "minishell: export: %s\n", strerror(errno));
		return (1);
	}
	free_node(key);
	free_node(value);
	return (0);
}

int	print_export(t_context *context, int output_fd)
{
	char		**cpy_env;
	int			i;
	int			count;
	int			min;

	count = context->env.len + context->export.len;
	cpy_env = my_malloc(count-- * sizeof(char *));
	if (!cpy_env)
		exit(MALLOC_FAIL_ERRNO);
	i = -1;
	while (++i < context->env.len)
		cpy_env[i] = ((char **)context->env.tab)[i];
	--i;
	while (++i - context->env.len < context->export.len)
		cpy_env[i] = ((char **)context->export.tab)[i - context->env.len];
	while (--count > 0)
	{
		min = get_min(cpy_env, context->env.len + context->export.len);
		if (!(cpy_env[min][0] == '_' && cpy_env[min][1] == '='))
			if (print_one(output_fd, cpy_env[min]))
				return (1);
		cpy_env[min] = NULL;
	}
	free_node(cpy_env);
	return (0);
}
