#include "minishell.h"
#include "libft.h"
#include <linux/fd.h>
#include <errno.h>
#include <string.h>

int	add_export_cmd(char **args, t_context *context);

int	ft_keycmp(char *key1, char *key2)
{
	int	i;

	i = -1;
	while (key1[++i] && key1[i] != '=' && key2[i] != '=')
		if (key1[i] != key2[i])
			return (key1[i] - key2[i]);
	if (key1[i] == key2[i]
		|| (!key1[i] && key2[i] == '=') || (!key1[i] && key2[i] == '='))
		return (0);
	if (!key1[i] || key1[i] == '=')
		return (-1);
	if (key2[i] == '=')
		return (1);
	printf("\n\n\n!!!!!!!!!!!!!!!!!\nPROB\n!!!!!!!!!!!!!!!!!!!!!\n\n\n\n"); // @TODO make tests (export_sheet.txt) and RM
	return (0);
}

int	get_min(char **cpy_env, int len)
{
	int	i;
	int	min;

	i = -1;
	min = -1;
	while (++i < len)
		if (cpy_env[i]
			&& (min == -1 || ft_keycmp(cpy_env[min], cpy_env[i]) > 0))
			min = i;
	return (min);
}

static char	*get_key(char *arg)
{
	int		i;
	char	*key;

	i = 0;
	while (arg[i] && arg[i] != '=')
		i++;
	key = ft_substr(arg, 0, i);
	add_node(key);
	return (key);
}

static char	*get_value(char *arg)
{
	int		i;
	char	*value;

	i = 0;
	while (arg[i] && arg[i] != '=')
		i++;
	if (!arg[i])
		return (NULL);
	value = ft_substr(arg, i + 1, ft_strlen(arg) - i - 1);
	add_node(value);
	return (value);
}

static int	print_one(int output_fd, char *var)
{
	char	*key;
	char	*value;

	key = get_key(var);
	value = get_value(var);
	if ((value && printf_fd(output_fd, "declare -x %s=\"%s\"\n", key, value) < 0)
		|| (!value && printf_fd(output_fd, "declare -x %s\n", key) < 0))
	{
		free_node(key);
		free_node(value);
		printf_fd(STDERR_FILENO, "minishell: export: %s\n", strerror(errno));
		return (1);
	}
	free_node(key);
	free_node(value);
	return (0);
}

int	print_export(t_context *context, int output_fd)
{
	char		**cpy_env;
	int			i;
	int			count;
	int			min;

	count = context->env.len + context->export.len;
	cpy_env = my_malloc(count * sizeof(char *));
	if (!cpy_env)
		exit(MALLOC_FAIL_ERRNO);
	i = -1;
	while (++i < context->env.len)
		cpy_env[i] = ((char **)context->env.tab)[i];
	--i;
	while (++i - context->env.len < context->export.len)
		cpy_env[i] = ((char **)context->export.tab)[i - context->env.len];
	while (count > 0)
	{
		min = get_min(cpy_env, context->env.len + context->export.len);
		if (!(cpy_env[min][0] == '_' && cpy_env[min][1] == '='))
			if (print_one(output_fd, cpy_env[min]))
				return (1);
		cpy_env[min] = NULL;
		count--;
	}
	free_node(cpy_env);
	return (0);
}

int	export_cmd(char **args, t_context *context, int input_fd, int output_fd)
{
	(void)input_fd;
	//if (!args) // @TODO ? rm
	//	error(GENERIC_ERRNO, __LINE__, __FILE__);
	if (!*args)
		return(print_export(context, output_fd));
	return(add_export_cmd(args, context));
}
