#ifndef MINISHELL_H
# define MINISHELL_H

# include "vector.h"
# include <stdio.h>

typedef t_vector	t_env;

# define MALLOC_FAIL_ERRNO 1
# define OTHER_ERRNO 2

# define ENV 1
# define EXPORT 2

# define MANUALLY_SET 0
# define UPDATE_WITH_CWD 1

typedef struct s_context
{
	t_vector	export;
	t_env		env;
	int			pwd_status;
	int			errno; // @TODO use this for every error
}	t_context;

typedef struct s_command
{
	char	*cmd;
	char	**args;
}	t_command;

typedef struct s_string
{
	char	*start;
	int		len;
}	t_string;

/* ### Env functions ### */

/* Initialize the env */
void		init_env(t_env *env, char **envp);

/* Get a value from a key in the env. The return is malloc'd */
char		*get_env_value(t_env *env, char *key);

/* Get the offset of a key in the env. Return -1 if the key doesn't exists */
int			get_env_offset(t_env *env, char *key);

/* Add a "key=value" malloc'd str in the env
	if key already exists, modify the value */
int			add_env_full(t_env *env, char *env_var)
			__attribute__ ((warn_unused_result));

/* Add a key=value node in the env
	if key already exists, modify the value */
int			add_env(t_env *env, char *key, char *value)
			__attribute__ ((warn_unused_result));

/* Remove a key=value node in the env
	return 0 on success, 1 if key doesn't exists */
int			remove_env(t_env *env, char *key);

/* ### Context functions ### */
int			init_context(t_context *context, char **envp);

int			exec(t_command cmd, t_context *context);

/* ### Builtin functions functions ### */

/*
	args : malloc'd array of malloc'd str
*/
typedef int			(*t_builtin_func)(char **args, t_context *context);

int			echo_cmd(char **args, t_context *context);
int			cd_cmd(char **args, t_context *context);
int			pwd_cmd(char **args, t_context *context);
int			export_cmd(char **args, t_context *context);
int			unset_cmd(char **args, t_context *context);
int			env_cmd(char **args, t_context *context);
int			exit_cmd(char **args, t_context *context);

int			cd(char *path, t_context *context);
void		unset(char *key, t_context *context, int flag);
int			add_export(char *arg, t_context *context);

/* ### Utils functions ### */

int			ft_streq(const char *str1, const char *str2); // @TODO rm and use libft
int			ft_lineeq(const char *str1, const char *str2);

#endif