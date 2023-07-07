/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   context.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlepille <vlepille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 17:38:57 by aboulest          #+#    #+#             */
/*   Updated: 2023/07/07 12:15:47 by vlepille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

void	init_context_values(t_context *context, int ac, char **av, char **envp)
{
	context->argc = ac;
	context->argv = av;
	context->in_fork = false;
	init_env(&context->env, envp);
	init_vec(&context->export, sizeof(char *));
	init_vec(&context->fds_open, sizeof(int));
	context->exit_value = 0;
	context->old_exit_value = 0;
	context->cwd = NULL;
}

int	init_context(t_context *context, int ac, char **av, char **envp)
{
	char	*shlvl;
	char	*tmp;

	init_context_values(context, ac, av, envp);
	context->pwd = getcwd(NULL, 0);
	add_node_ignore_null(context->pwd);
	add_export("PWD", context);
	context->oldpwd = get_env_value(&context->env, "OLDPWD");
	add_export("OLDPWD", context);
	shlvl = get_env_value(&context->env, "SHLVL");
	if (shlvl)
	{
		tmp = ft_itoa(ft_atoi(shlvl) + 1);
		if (!tmp)
			error(MALLOC_FAIL_ERRNO, __LINE__, __FILE__);
		add_env(&context->env, "SHLVL", tmp);
		free(tmp);
	}
	else
		add_export("SHLVL=1", context);
	free_node(shlvl);
	return (0);
}
