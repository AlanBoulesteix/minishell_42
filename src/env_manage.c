#include "minishell.h"
#include <stdlib.h>
#include <stdio.h>

void	init_env(t_env *env, char **envp)
{
	int	errno;

	init_vector(env, sizeof(char *));
	while (*envp)
	{
		errno = add_to_env_full(env, *(envp++));
		if (errno)
			exit((perror("Error"), errno));
	}
}

int	keyeq(char *key, char *envstr)
{
	int	i;

	i = 0;
	if (!envstr || !envstr[i])
		exit(OTHER_ERRNO); // @TODO CHANGE AND EXIT CLEANLY
	while (key[i] && key[i] == envstr[i])
		i++;
	return (i * (envstr[i] == '=' && !key[i]));
}

// @TODO rm this one, use libft_strlen
int	ft_strlen(char *str)
{
	int	i;

	for (i = 0; str[i]; i++);
	return (i);
}

char	*get_env_value(t_env *env, char *key)
{
	int		i;
	int		j;
	int		key_len;
	char	*res;

	i = -1;
	key_len = 0;
	while (++i < env->len && !key_len)
		key_len = keyeq(key, ((char **)env->tab)[i]);
	if (!key_len)
		return (NULL);
	res = malloc(ft_strlen(((char **)env->tab)[--i] + key_len + 1) + 1);
	j = -1;
	while (((char **)env->tab)[i][key_len + ++j + 1])
		res[j] = ((char **)env->tab)[i][key_len + j + 1];
	res[j] = 0;
	return (res);
}
