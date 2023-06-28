#include "minishell.h"
#include "libft.h"

int		get_env_offset(t_env *env, char *key);

static int	get_keylen(char *arg)
{
	int	len;

	len = 0;
	while (arg[len] && arg[len] != '=')
		len++;
	return (len);
}

int	valid(char *arg, int len)
{
	int	i;

	if (!len)
		return (0);
	if (arg[0] >= '0' && arg[0] <= '9')
		return (0);
	i = 0;
	while (i < len)
	{
		if (!((arg[i] >= '0' && arg[i] <= '9')
				|| (arg[i] >= 'A' && arg[i] <= 'Z')
				|| (arg[i] >= 'a' && arg[i] <= 'z')
				|| arg[i] == '_'))
			return (0);
		i++;
	}
	return (1);
}

void	add_export_append(char *arg, const int keylen, t_context *context)
{
	char	*old;
	char	*append;

	arg[keylen] = 0;
	old = get_env_value(&context->env, arg);
	unset(arg, context, ENV | EXPORT);
	if (old)
		append = ft_strjoin(old, arg + keylen + 2);
	else
		append = ft_strdup(arg + keylen + 2);
	add_node(append);
	add_env(&context->env, arg, append);
	arg[keylen] = '+';
	free_node(arg);
}

void	add_export_base(char *arg, t_context *context, const int keylen, int add_mode)
{
	char	*dup;

	if (add_mode == EXPORT_APPEND)
		return ((void)add_export_append(arg, keylen, context));
	dup = ft_strdup(arg);
	add_node(dup);
	if (add_mode == EXPORT_SET)
	{
		dup[keylen] = 0;
		unset(dup, context, ENV | EXPORT);
		dup[keylen] = '=';
		add_env_full(&context->env, dup);
	}
	else if (get_env_offset(&context->env, dup) < 0)
	{
		unset(dup, context, EXPORT);
		add_vec(&context->export, &dup);
	}
}

static int	add_exception(char *arg, t_context *context, const int keylen, int add_mode)
{
	if (!ft_strncmp(arg, "PWD", keylen))
	{
		// if (add_mode)
		// {
		// 	free_node(context->pwd);
		// 	context->pwd = ft_strdup(arg + keylen + 1 + add_mode);
		// 	add_node(context->pwd);
		// 	return (0);
		// }
		if (pwd_is_update(context) && add_mode == EXPORT_NULL)
		{
			unset("PWD", context, ENV | EXPORT);
			add_env(&context->env, "PWD", context->pwd);
			return (1);
		}
	}
	if (!ft_strncmp(arg, "OLDPWD", keylen))
	{
		// if (add_mode)
		// {
		// 	free_node(context->oldpwd);
		// 	context->oldpwd = NULL;
		// 	return (0);
		// }
		if (context->oldpwd && add_mode == EXPORT_NULL)
		{
			unset("OLDPWD", context, ENV | EXPORT);
			add_env(&context->env, "OLDPWD", context->oldpwd);
			return (1);
		}
	}
	return (0);
}

int	get_export_mode(char *arg, int keylen)
{
	if (keylen > 0 && arg[keylen - 1] == '+' && arg[keylen] == '=')
		return (EXPORT_APPEND);
	if (arg[keylen] == '=')
		return (EXPORT_SET);
	return (EXPORT_NULL);
}

void	pwd_update(t_context *context)
{
	context->pwd = get_env_value(&context->env, "PWD");
	context->oldpwd = get_env_value(&context->env, "OLDPWD");
}

int	add_export(char *arg, t_context *context)
{
	int	keylen;
	int	add_mode;

	keylen = get_keylen(arg);
	add_mode = get_export_mode(arg, keylen);
	keylen -= add_mode == EXPORT_APPEND;
	if (!valid(arg, keylen))
	{
		printf_fd(STDERR_FILENO, "minishell: export: `%s': not a valid identifier\n", arg);
		return(1);
	}
	else if (!add_exception(arg, context, keylen, add_mode))
		add_export_base(arg, context, keylen, add_mode);
	if (add_mode)
		pwd_update(context);
	return (0);
}

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
