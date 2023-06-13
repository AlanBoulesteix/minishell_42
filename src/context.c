/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   context.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlepille <vlepille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 17:38:57 by aboulest          #+#    #+#             */
/*   Updated: 2023/06/13 14:10:33 by vlepille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

int	init_context(t_context *context, char **envp)
{
	char	*shlvl;

	context->in_fork = false;
	init_env(&context->env, envp);
	init_vec(&context->export, sizeof(char *));
	context->exit_value = 0;
	context->pwd_status = UPDATE_WITH_CWD;
	add_export("PWD", context);
	cd(".", context);
	add_export("OLDPWD", context);
	shlvl = get_env_value(&context->env, "SHLVL");
	if (shlvl)
	{
		add_env(&context->env, "SHLVL", ft_itoa(ft_atoi(shlvl) + 1)); // @TODO free itoa return
	}
	else
		add_export("SHLVL=1", context);
	free(shlvl);
	return (0);
}
