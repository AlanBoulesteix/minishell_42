/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   context_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlepille <vlepille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 16:57:09 by aboulest          #+#    #+#             */
/*   Updated: 2023/07/07 12:13:36 by vlepille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

int	pwd_is_update(t_context *context)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (0);
	add_node(cwd);
	if (ft_streq(cwd, context->pwd))
	{
		free_node(cwd);
		return (1);
	}
	free_node(cwd);
	return (0);
}
