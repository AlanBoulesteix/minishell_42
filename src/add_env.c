#include "minishell.h"
#include <stdlib.h>

int	keyeq(char *key, char *envstr);

int	get_env_offset(t_env *env, char *key)
{
	int	i;

	i = 0;
	while (i < env->len && !keyeq(key, ((char **)env->tab)[i]))
		i++;
	if (i == env->len)
		return (-1);
	return (i);
}

int	add_env_full(t_env *env, char *env_var)
{
	int	i;
	int	ret;

	i = 0;
	while (env_var[i] && env_var[i] != '=')
		i++;
	if (!env_var[i])
		return (GENERIC_ERRNO);
	env_var[i] = 0;
	ret = get_env_offset(env, env_var);
	env_var[i] = '=';
	if (ret < 0)
		return (add_vec(env, env_var));
	free(((char **)env->tab)[ret]);
	((char **)env->tab)[ret] = env_var;
	return (0);
}

// @TODO ? verif value and key not null
int	add_env(t_env *env, char *key, char *value)
{
	const int	size = ft_strlen(key) + ft_strlen(value) + 2;
	char		*res;
	int			i;
	int			j;

	res = malloc(size * sizeof(char));
	if (!res)
		return (MALLOC_FAIL_ERRNO);
	i = -1;
	while (key[++i])
		res[i] = key[i];
	res[i++] = '=';
	j = -1;
	while (value[++j])
		res[i++] = value[j];
	res[i] = 0;
	return (add_env_full(env, res));
}

int	remove_env(t_env *env, char *key)
{
	int	offset;

	offset = get_env_offset(env, key);
	if (offset < 0)
		return (1);
	remove_vec(env, offset);
	return (0);
}
