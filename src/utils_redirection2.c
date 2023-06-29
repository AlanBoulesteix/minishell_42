/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_redirection2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlepille <vlepille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 16:04:34 by vlepille          #+#    #+#             */
/*   Updated: 2023/06/29 16:05:56 by vlepille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <errno.h>
#include <string.h>

void	close_fd(t_cmd *cmd)
{
	if (cmd->input_fd > 2)
		close(cmd->input_fd);
	if (cmd->output_fd > 2)
		close(cmd->output_fd);
}

int	error_is_directory(char *file, t_context *context)
{
	printf_fd(STDERR_FILENO, "minishell: %s: Is a directory\n", file);
	context->exit_value = 1;
	return (-1);
}

void	print_error_redir(char *file, int fd, t_context *context)
{
	if (fd == -1)
	{
		printf_fd(STDERR_FILENO, "minishell: %s: %s\n", file, strerror(errno));
		context->exit_value = 1;
	}
}
