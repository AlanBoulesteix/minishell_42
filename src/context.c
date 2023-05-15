/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   context.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlepille <vlepille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 17:38:57 by aboulest          #+#    #+#             */
/*   Updated: 2023/05/15 16:25:22 by vlepille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stddef.h>

int	init_context(t_context *context, char **envp)
{
	context->input = NULL;
	context->garb = NULL;
	init_env(&context->env, envp);
	return (0);
}
