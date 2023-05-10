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

static int	valid(char *arg, int len)
{
	int	i;

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

void	add_export(char *arg, t_context *context, const int keylen)
{
	if ((arg)[keylen] == '=')
	{
		(arg)[keylen] = 0;
		unset(arg, context, ENV | EXPORT);
		(arg)[keylen] = '=';
		context->errno = add_env_full(&context->env, ft_strdup(arg));
		if (context->errno)
			exit(context->errno);
	}
	else if (get_env_offset(&context->env, arg) < 0)
	{
		unset(arg, context, EXPORT);
		context->errno = add_vec(&context->export, ft_strdup(arg));
		if (context->errno)
			exit(context->errno);
	}
}

static int	add_exception(char *arg, t_context *context, const int keylen)
{
	if (!ft_strncmp(arg, "PWD", keylen))
	{

	}
	return (0);
}

int	add_export_cmd(char **args, t_context *context)
{
	int	keylen;
	int	res;

	res = 0;
	while (*args)
	{
		keylen = get_keylen(*args);
		if (!valid(*args, keylen))
		{
			printf("minishell: export: `%s': not a valid identifier\n", *args); // @TODO STDERR
			res = 1;
		}
		else if (!add_exception(*args, context, keylen))
			add_export(*args, context, keylen);
		args++;
	}
	return (res);
}

