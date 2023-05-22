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

void	add_export_base(char *arg, t_context *context, const int keylen)
{
	char	*dup;
	int		exit_value;

	dup = ft_strdup(arg);
	if (!dup)
		exit(MALLOC_FAIL_ERRNO);
	if (dup[keylen] == '=')
	{
		dup[keylen] = 0;
		unset(dup, context, ENV | EXPORT);
		dup[keylen] = '=';
		add_env_full(&context->env, dup);
	}
	else if (get_env_offset(&context->env, dup) < 0)
	{
		unset(dup, context, EXPORT);
		exit_value = add_vec(&context->export, dup);
		if (exit_value)
			exit(exit_value);
	}
}

static int	add_exception(char *arg, t_context *context, const int keylen)
{
	char	*cwd;

	if (!ft_strncmp(arg, "PWD", keylen))
	{
		if (arg[keylen] == '=')
		{
			context->pwd_status = MANUALLY_SET;
			return (0);
		}
		else if (context->pwd_status == UPDATE_WITH_CWD)
		{
			unset("PWD", context, ENV | EXPORT);
			cwd = getcwd(NULL, 0);
			if (!cwd)
				exit(MALLOC_FAIL_ERRNO);
			add_env(&context->env, "PWD", cwd);
			free(cwd);
			return (1);
		}
	}
	return (0);
}

int	add_export(char *arg, t_context *context)
{
	int	keylen;

	keylen = get_keylen(arg);
	if (!valid(arg, keylen))
	{
		printf_fd(STDERR_FILENO, "minishell: export: `%s': not a valid identifier\n", arg);
		return(1);
	}
	else if (!add_exception(arg, context, keylen))
		add_export_base(arg, context, keylen);
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

