#ifndef MINISHELL_H
# define MINISHELL_H

# include "vector.h"

# define MALLOC_FAIL_ERRNO 1
# define OTHER_ERRNO 2

typedef t_vector	t_env;

typedef struct s_context
{
	char	*input;
	t_env	env;
}	t_context;

/* ### Env functions ### */

/* Initialize the env */
void	init_env(t_env *env, char **envp);

/* Get a value from a key in the env. The return is malloc'd */
char	*get_env_value(t_env *env, char *key);

/* Add a "key=value" malloc'd str in the env
	if key already exists, modify the value */
int		add_env_full(t_env *env, char *env_var);

/* Add a key=value node in the env
	if key already exists, modify the value */
int		add_env(t_env *env, char *key, char *value);

/* Remove a key=value node in the env
	return 0 on success, 1 if key doesn't exists */
int		remove_env(t_env *env, char *key);

/* ### Context functions ### */
int		init_context(t_context *context, char **envp);

int		ft_streq(char *str1, char *str2);

#endif