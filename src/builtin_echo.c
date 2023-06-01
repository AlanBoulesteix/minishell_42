#include "minishell.h"
#include <string.h>
#include <errno.h>

static int	option_newline(char *arg)
{
	int	i;

	if (!arg)
		return (1);
	if (arg[0] != '-')
		return (0);
	i = 1;
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

static int	get_len(char **args)
{
	int	len;

	len = 0;
	while (*args)
	{
		len += ft_strlen(*args);
		len += 1;
		args++;
	}
	return (len);
}

int	echo_cmd(char **args, t_context *context, int input_fd, int output_fd)
{
	char		*str;
	int			opt_nl;
	int			i;
	int			j;

	(void)input_fd;
	(void)context;
	if (!*args)
		return (0);
	opt_nl = option_newline(*args);
	if (opt_nl)
		args++;
	str = malloc(sizeof(char) * (get_len(args) + 1));
	i = 0;
	while (*args)
	{
		j = 0;
		while ((*args)[j])
		{
			str[i] = (*args)[j];
			i++;
			j++;
		}
		if (*(args + 1))
			str[i++] = ' ';
		args++;
	}
	if (!opt_nl)
		str[i++] = '\n';
	str[i] = '\0';
	if (printf_fd(output_fd, "%s", str) < 0)
	{
		printf_fd(STDERR_FILENO, "minishell: echo: write error: %s\n", strerror(errno));
		return (1);
	}
	return (0);
}
