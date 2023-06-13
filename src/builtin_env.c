#include "minishell.h"
#include <string.h>
#include <errno.h>

static int	is_shlvl(char *str)
{
	int	i;
	int	len;

	i = 0;
	while (str[i] == ' ')
		i++;
	if (!ft_isdigit(str[i]))
		return (0);
	len = 0;
	while (ft_isdigit(str[i + len]))
		len++;
	if (len >= 4 && !(str[i] == '1' && str[i + 1] == '0' && str[i + 2] == '0'
			&& str[i + 3] == '0'))
		return (-1);
	i += len;
	while (str[i] == ' ')
		i++;
	return (!str[i]);
}

static void	initialize(t_context *context, char **old_shlvl)
{
	char	*new_shlvl;

	if (context->in_fork)
	{
		*old_shlvl = get_env_value(context->env.tab, "SHLVL");
		if (*old_shlvl)
		{
			if (is_shlvl(*old_shlvl) == 1)
				new_shlvl = ft_itoa(ft_atoi(*old_shlvl) - 1);
			else if (is_shlvl(*old_shlvl) == -1)
				new_shlvl = ft_strdup("1");
			else
				new_shlvl = ft_strdup("0");
		}
		else
			new_shlvl = ft_strdup("0");
		add_env(&context->env, "SHLVL", new_shlvl);
		free(new_shlvl);
	}
}

int	env_cmd(char **args, t_context *context, int input_fd, int output_fd)
{
	int		i;
	char	*old_shlvl;

	(void)input_fd;
	(void) args;
	i = 0;
	initialize(context, &old_shlvl);
	while (i < context->env.len)
	{
		if (printf_fd(output_fd, "%s\n", ((char **)context->env.tab)[i]) < 0)
		{
			printf_fd(STDERR_FILENO, "env: write error: %s\n", strerror(errno));
			return (125);
		}
		i++;
	}
	if (context->in_fork)
	{
		if (old_shlvl)
			add_env(&context->env, "SHLVL", old_shlvl);
		else
			remove_env(&context->env, "SHLVL");
		free(old_shlvl);
	}
	return (0);
}
