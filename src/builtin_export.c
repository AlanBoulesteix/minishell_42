#include "minishell.h"
#include "libft.h"

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

void	print_export(t_context *context)
{
	char		**cpy_env;
	int			i;
	int			count;
	int			min;

	cpy_env = malloc((context->env.len + context->export.len) * sizeof(char *));
	if (!cpy_env)
		exit(MALLOC_FAIL_ERRNO);
	i = -1;
	while (++i < context->env.len)
		cpy_env[i] = ((char **)context->env.tab)[i];
	--i;
	while (++i - context->env.len < context->export.len)
		cpy_env[i] = ((char **)context->export.tab)[i - context->env.len];
	count = context->env.len + context->export.len;
	while (count > 0)
	{
		min = get_min(cpy_env, context->env.len + context->export.len);
		if (!(cpy_env[min][0] == '_' && cpy_env[min][1] == '='))
			printf("%s\n", cpy_env[min]); // @TODO print key="value" instead of key=value
		cpy_env[min] = NULL;
		count--;
	}
	free(cpy_env);
}

int	export_cmd(char **args, t_context *context)
{
	int	exit_value;

	exit_value = 0;
	if (!args) // @TODO ? rm
		error(GENERIC_ERRNO, __LINE__);
	if (!*args)
		print_export(context);
	else
		exit_value = add_export_cmd(args, context);
	return (exit_value);
}
