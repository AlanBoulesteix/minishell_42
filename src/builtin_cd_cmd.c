/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlepille <vlepille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 14:18:28 by vlepille          #+#    #+#             */
/*   Updated: 2023/06/29 14:18:37 by vlepille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cd_cmd(char **args, t_context *context, int input_fd, int output_fd)
{
	(void)input_fd;
	(void)output_fd;
	if (!args[0])
		return (cd(NULL, context));
	if (args[1])
		return (
			printf_fd(STDERR_FILENO, "minishell: cd: too many arguments\n"), 1);
	return (cd(args[0], context));
}
