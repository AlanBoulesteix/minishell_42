#include "minishell.h"
#include "libft.h"
#include <unistd.h>

static int	print_err_numarg(const char *str)
{
	printf_fd(
		STDERR_FILENO, "bash: exit: %s: numeric argument required\n", str);
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
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
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
	if (str[i] && str[i] != ' ' && (str[i] < 9 || str[i] > 13))
		return (print_err_numarg(str));
	return (res);
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
			(write(STDERR_FILENO, "bash: exit: too many arguments\n", 31), 1));
	if (!args[0])
		exit(0);
	exit(ft_atoi_exit(args[0]));
}
