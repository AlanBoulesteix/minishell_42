#ifndef MINISHELL_H
# define MINISHELL_H

# include "vector.h"

typedef t_vector t_env;

typedef struct s_context
{
	char	*input;
	t_env	env;
}	t_context;

/* ### Env functions ### */

/*
	Initialize the env
*/
void	init_env(t_env *env);

/*
	Get a value from a key in the env. The return is malloc
*/
char	*get_env(t_env *env, char *key);

/*
	Add a key=value node in the env, if exists, modify
*/
int		add_to_env(t_env *env, char *key, char *value);

/* ### Context functions ### */
int		init_context(t_context *context);

int		ft_streq(char *str1, char *str2);

#endif