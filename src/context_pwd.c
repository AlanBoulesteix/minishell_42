/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   context_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulest <aboulest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 16:57:09 by aboulest          #+#    #+#             */
/*   Updated: 2023/06/29 16:57:10 by aboulest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

int	pwd_is_update(t_context *context)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	add_node(cwd);
	if (ft_streq(cwd, context->pwd))
	{
		free_node(cwd);
		return (1);
	}
	free_node(cwd);
	return (0);
}
