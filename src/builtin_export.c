/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlepille <vlepille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 14:21:30 by vlepille          #+#    #+#             */
/*   Updated: 2023/06/29 14:30:44 by vlepille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <linux/fd.h>

int	add_export_cmd(char **args, t_context *context)
{
	int	res;

	res = 0;
	while (*args)
	{
		res += add_export(*args, context);
		args++;
	}
	return (!!res);
}

int	print_export(t_context *context, int output_fd);

int	export_cmd(
	char **args, t_context *context, int input_fd, int output_fd)
{
	(void)input_fd;
	if (!*args)
		return (print_export(context, output_fd));
	return (add_export_cmd(args, context));
}
