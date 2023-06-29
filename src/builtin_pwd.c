/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlepille <vlepille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 14:23:59 by vlepille          #+#    #+#             */
/*   Updated: 2023/06/29 14:24:00 by vlepille         ###   ########.fr       */
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
	(void)context;
	cwd = getcwd(NULL, 0);
	add_node(cwd);
	if (printf_fd(output_fd, "%s\n", cwd) < 0)
	{
		free_node(cwd);
		printf_fd(STDERR_FILENO, "minishell: pwd: %s\n", strerror(errno));
		return (1);
	}
	free_node(cwd);
	return (0);
}
