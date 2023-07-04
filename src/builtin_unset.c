/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulest <aboulest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 14:24:05 by vlepille          #+#    #+#             */
/*   Updated: 2023/07/04 17:03:39 by aboulest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

void	unset(char *key, t_context *context, int flag)
{
	int	i;

	if (flag & ENV)
		remove_env(&context->env, key);
	if (!(flag & EXPORT))
		return ;
	i = 0;
	while (i < context->export.len)
	{
		if (ft_streq(((char **)context->export.tab)[i], key))
			break ;
		i++;
	}
	if (i < context->export.len)
	{
		free_node(((char **)context->export.tab)[i]);
		remove_vec(&context->export, i);
	}
}

int	unset_cmd(char **args, t_context *context, int input_fd, int output_fd)
{
	(void)input_fd;
	(void)output_fd;
	while (*args)
	{
		if (ft_streq(*args, "PWD"))
		{
			if (context->pwd)
			{
				if (context->cwd)
					free_node(context->cwd);
				context->cwd = context->pwd;
			}
			context->pwd = NULL;
		}
		if (ft_streq(*args, "OLDPWD"))
		{
			free_node(context->oldpwd);
			context->oldpwd = NULL;
		}
		unset(*args, context, ENV | EXPORT);
		args++;
	}
	return (0);
}
