#include "minishell.h"

int	get_equal_offset(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (i);
		i++;
	}
	return (0);
}

void	join_str_vec(t_vector *res, char *src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		add_vec(res, src + i);
		i++;
	}
}

int	add_exit_var(t_vector *res, t_context *context)
{
	char	*tmp;

	tmp = ft_itoa(context->old_exit_value);
	add_node(tmp);
	join_str_vec(res, tmp);
	free_node(tmp);
	return (2);
}

int	add_var(t_vector *res, char *src, t_context *context)
{
	int		i;
	char	*var;
	char	c;

	if (src[1] == '?')
		return (add_exit_var(res, context));
	if (ft_isdigit(src[1]))
	{
		if (src[1] - '0' < context->argc)
			join_str_vec(res, context->argv[src[1] - '0']);
		return (2);
	}
	i = 1;
	while (ft_isalnum(src[i]) || src[i] == '_')
		i++;
	c = src[i];
	src[i] = 0;
	var = get_env_value(&context->env, src + 1);
	src[i] = c;
	if (var)
		join_str_vec(res, var);
	return (i);
}

char	*expend_special_export(char *src, t_context *context)
{
	t_vector	res;
	int			i;
	bool		in_simple;
	bool		in_double;

	i = -1;
	init_vec(&res, sizeof(char));
	in_simple = false;
	in_double = false;
	while (src[++i])
	{
		if (src[i] == '\'' && !in_double)
			in_simple = !in_simple;
		else if (src[i] == '\"' && !in_simple)
			in_double = !in_double;
		else if (is_var(src + i) && !in_simple)
			i += add_var(&res, src + i, context) - 1;
		else
			add_vec(&res, src + i);
	}
	add_vec(&res, "");
	return (res.tab);
}

char	*expend_export(char *src, t_vector *tokens, int i, t_context *context)
{
	int	equal_offset;

	equal_offset = get_equal_offset(src);
	if (equal_offset && valid(src, equal_offset))
		return (expend_special_export(src, context));
	return (expend_default(src, tokens, i, context));
}
