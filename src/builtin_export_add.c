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

static void	add(char **args, t_context *context, const int keylen)
{
	if ((*args)[keylen] == '=')
	{
		(*args)[keylen] = 0;
		unset(*args, context, ENV | EXPORT);
		(*args)[keylen] = '=';
		context->errno = add_env_full(&context->env, ft_strdup(*args));
		if (context->errno)
			exit(context->errno);
	}
	else if (get_env_offset(&context->env, *args) < 0)
	{
		unset(*args, context, EXPORT);
		context->errno = add_vec(&context->export, ft_strdup(*args));
		if (context->errno)
			exit(context->errno);
	}
}

int	add_export(char **args, t_context *context)
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
		else
			add(args, context, keylen);
		args++;
	}
	return (res);
}

