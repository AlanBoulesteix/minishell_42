/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlepille <vlepille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 14:19:47 by vlepille          #+#    #+#             */
/*   Updated: 2023/07/06 16:38:46 by vlepille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <unistd.h>

static int	print_err_numarg(const char *str)
{
	printf_fd(
		STDERR_FILENO, "minishell: exit: %s: numeric argument required\n", str);
	return (2);
}

static int	detect_overflow(long long res, int next_digit, int sign)
{
	const long long	next_res = res * 10 + (next_digit * sign);

	if (sign == 1 && next_res < res)
		return (1);
	if (sign == -1 && next_res > res)
		return (1);
	return (0);
}

static int	ft_atoi_exit(const char *str)
{
	int			i;
	long long	res;
	int			sign;

	i = 0;
	res = 0;
	while (is_sp(str[i]) || (str[i] >= 9 && str[i] <= 13))
		i++;
	sign = (str[i] != '-') * 2 - 1;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (detect_overflow(res, str[i] - '0', sign))
			return (print_err_numarg(str));
		res = res * 10 + ((str[i] - '0') * sign);
		i++;
	}
	if (str[i] && !is_sp(str[i]) && (str[i] < 9 || str[i] > 13))
		return (print_err_numarg(str));
	return (res);
}

void	ft_exit(int exit_value)
{
	printf_fd(STDERR_FILENO, "exit\n");
	exit(exit_value);
}

int	exit_cmd(char **args, t_context *context, int input_fd, int output_fd)
{
	(void)context;
	(void)input_fd;
	(void)output_fd;
	if (!context->in_fork)
		printf_fd(STDERR_FILENO, "exit\n");
	if (args[0] && args[1])
		return (
			(printf_fd(
					STDERR_FILENO, "minishell: exit: too many arguments\n"), 1));
	if (!args[0])
		exit(context->old_exit_value);
	exit(ft_atoi_exit(args[0]));
}
