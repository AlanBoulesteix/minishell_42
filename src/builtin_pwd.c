/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlepille <vlepille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 14:23:59 by vlepille          #+#    #+#             */
/*   Updated: 2023/07/07 12:28:11 by vlepille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

int	pwd_cmd(char **args, t_context *context, int input_fd, int output_fd)
{
	char	*cwd;

	(void)input_fd;
	(void)args;
	cwd = getcwd(NULL, 0);
	add_node_ignore_null(cwd);
	if (!cwd)
	{
		if (context->pwd)
			printf_fd(output_fd, "%s\n", context->pwd);
		else if (context->cwd)
			printf_fd(output_fd, "%s\n", context->cwd);
		else
			return (printf_fd(2, "pwd: getcwd: %s\n", strerror(errno)), 1);
		return (0);
	}
	if (printf_fd(output_fd, "%s\n", cwd) < 0)
	{
		free_node(cwd);
		printf_fd(STDERR_FILENO, "minishell: pwd: %s\n", strerror(errno));
		return (1);
	}
	free_node(cwd);
	return (0);
}
