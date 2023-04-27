#ifndef MINISHELL_H
# define MINISHELL_H

typedef struct s_context
{
	int	exit;
}	t_context;

typedef struct s_command
{
	char	*cmd;
	char	**args;
}	t_command;

int			init_context(t_context *context);
int			exec(t_command cmd, t_context *context);

typedef int	(*t_builtin_func)(char **args, t_context *context);
int			ft_echo(char **args, t_context *context);
int			ft_cd(char **args, t_context *context);
int			ft_pwd(char **args, t_context *context);
int			ft_export(char **args, t_context *context);
int			ft_unset(char **args, t_context *context);
int			ft_env(char **args, t_context *context);
int			ft_exit(char **args, t_context *context);

int			ft_streq(const char *str1, const char *str2);
int			ft_lineeq(const char *str1, const char *str2);

#endif