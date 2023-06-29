#include "minishell.h"
#include <string.h>
#include <errno.h>

static int	option_newline(char *arg)
{
	int	i;

	if (!arg)
		return (0);
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

void	echo_loop(char ***args, char *str, int *i)
{
	int	j;

	j = 0;
	while ((*(*args))[j])
	{
		str[(*i)] = (*(*args))[j];
		(*i)++;
		j++;
	}
	if (*((*args) + 1))
		str[(*i)++] = ' ';
	(*args)++;
}

int	echo_cmd(char **args, t_context *context, int input_fd, int output_fd)
{
	char		*str;
	int			opt_nl;
	int			i;
	char		**tmp;

	(void)input_fd;
	(void)context;
	tmp = args;
	opt_nl = option_newline(*tmp);
	while (option_newline(*tmp))
		tmp++;
	str = my_malloc(sizeof(char) * (get_len(tmp) + 1 + !*tmp));
	i = 0;
	while (*tmp)
		echo_loop(&tmp, str, &i);
	if (!opt_nl)
		str[i++] = '\n';
	str[i] = '\0';
	if (printf_fd(output_fd, "%s", str) < 0)
	{
		printf_fd(STDERR_FILENO,
			"minishell: echo: write error: %s\n", strerror(errno));
		return (1);
	}
	return (0);
}
