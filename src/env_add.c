#include "minishell.h"
#include "libft.h"
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

void	add_env_full(t_env *env, char *env_var)
{
	int	i;
	int	ret;

	i = 0;
	while (env_var[i] && env_var[i] != '=')
		i++;
	if (!env_var[i])
		error_str("add_env_full: env_var doesn't contain '='",
			__LINE__, __FILE__);
	env_var[i] = 0;
	ret = get_env_offset(env, env_var);
	env_var[i] = '=';
	if (ret < 0)
	{
		ret = add_vec(env, &env_var);
		if (ret)
			error(GENERIC_ERRNO, __LINE__, __FILE__);
		ret = add_vec(env, &(char *){NULL});
		if (ret)
			error(GENERIC_ERRNO, __LINE__, __FILE__);
		env->len--;
		return ;
	}
	free_node(((char **)env->tab)[ret]);
	((char **)env->tab)[ret] = env_var;
}

// @TODO ? verif value and key not null
void	add_env(t_env *env, char *key, char *value)
{
	const int	size = ft_strlen(key) + ft_strlen(value) + 2;
	char		*res;
	int			i;
	int			j;

	res = my_malloc(size * sizeof(char));
	if (!res)
		error(MALLOC_FAIL_ERRNO, __LINE__, __FILE__);
	i = -1;
	while (key[++i])
		res[i] = key[i];
	res[i++] = '=';
	j = -1;
	while (value[++j])
		res[i++] = value[j];
	res[i] = 0;
	add_env_full(env, res);
}

int	remove_env(t_env *env, char *key)
{
	int	offset;

	offset = get_env_offset(env, key);
	if (offset < 0)
		return (1);
	free_node(((char **)env->tab)[offset]);
	remove_vec(env, offset);
	((char **)env->tab)[env->len] = NULL;
	return (0);
}
