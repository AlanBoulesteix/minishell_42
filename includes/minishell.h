/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlepille <vlepille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 11:59:20 by aboulest          #+#    #+#             */
/*   Updated: 2023/06/20 13:31:47 by vlepille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include "libft.h"
# include "printf_fd.h"
# include "vector.h"
# include <stdbool.h>

# define UNDEFINE -1
# define NO_OP 0
# define PP 1
# define OR 2
# define AND 3

# define GENERIC_ERRNO -1
# define SUCCESS_ERRNO 0
# define MALLOC_FAIL_ERRNO 1
# define FORK_FAIL_ERRNO 2
# define EXECVE_FAIL_ERRNO 3
# define PIPE_FAIL_ERRNO 4
# define OPEN_FAIL_ERRNO 5
# define CLOSE_FAIL_ERRNO 6
# define DUP2_FAIL_ERRNO 7
# define SIGNALS_FAIL_ERRNO 8

# define WORD 0b1
# define OPE 0b10
# define PAREN_OPEN 0b100
# define PAREN_CLOSED 0b1000
# define REDIR 0b10000
# define NEWLINE 0b100000

# define REDIR_IN 1
# define REDIR_OUT 2
# define REDIR_OUT_EXTEND 3
# define HERE_DOC 4
# define CMD 5

# define ENV 1
# define EXPORT 2

# define MANUALLY_SET 0
# define UPDATE_WITH_CWD 1

# ifndef DEBUG
#  define DEBUG 0
# else
#  define DEBUG 1
# endif

typedef t_vector	t_env;

typedef struct s_context
{
	t_env			env;
	t_vector		export;
	char			**argv;
	char			*input;
	char			*pwd;
	char			*oldpwd;
	bool			stop;
	bool			in_fork;
	int				argc;
	unsigned char	exit_value;
}	t_context;

typedef struct s_block
{
	char			*start;
	struct s_block	*left;
	struct s_block	*right;
	int				len;
	int				op;
}	t_block;

typedef struct s_token
{
	char	*s_str;
	char	*f_str;
	int		type;

}	t_token;

typedef struct s_cmd
{
	char	*path;
	char	**cmd;
	int		input_fd;
	int		output_fd;
}	t_cmd;

/* ### Utils ### */

void			error(int errno, int line, char *file);
void			error_str(char *str, int line, char *file);

void			*my_malloc(size_t size);
void			free_all(void)
				__attribute__((destructor));
void			free_node(void *add);
void			add_node(void *ptr);

int				ft_streq(const char *str1, const char *str2);
int				ft_lineeq(const char *str1, const char *str2);

/// @brief Return the length of an integer
/// @param nbr The integer to get the length
/// @return The length of the integer
int				nbrlen(int nbr);
/// @brief Copy the value of an integer in the string
/// @param s1 The string to copy the integer in
/// @param nbr The integer to copy
/// @param index The index of the string to start the copy
void			cpy_nbr(char *s1, int nbr, int *index);

/* ### Context functions ### */

/// @brief Init the context from the envp
/// @param context The context
/// @param envp The envp
/// @return 0 on success, 1 on error
int				init_context(
					t_context *context, int argc, char **argv, char **envp);
int				pwd_is_update(t_context *context);

/* ### Env functions ### */

/// @brief Init the env from the envp
/// @param env The env
/// @param envp The envp
void			init_env(t_env *env, char **envp);

/// @brief Get a value from a key in the env
/// @param env The env
/// @param key The key
/// @return The value, malloc'd
char			*get_env_value(t_env *env, char *key);

/// @brief Get the offset of a key in the env
/// @param env The env
/// @param key The key
/// @return The offset of the key in the env, or -1 if the key doesn't exists
int				get_env_offset(t_env *env, char *key);

/// @brief Add a "key=value" str in the env
/// @brief if key already exists modify the value
/// @param env The env
/// @param env_var The "key=value" malloc'd str
void			add_env_full(t_env *env, char *env_var);

/// @brief Add a key=value node in the env,
/// @brief if key already exists modify the value
/// @param env The env
/// @param key The key
/// @param value The value
void			add_env(t_env *env, char *key, char *value);

/// @brief Remove a key=value node in the env
/// @param env The env
/// @param key The key
/// @return 0 on success, 1 if key doesn't exists
int				remove_env(t_env *env, char *key);


/* ### Signals ### */

void			set_parent_signals(void);
void			set_children_signals(void);
void			set_wait_signals(void);
void			set_heredoc_signal(void);


/* ### Parsing ### */

/*# Error tokens #*/
int				is_token(char *str);
void			skip(char *str, int *i);
int				check_token(char *str);
int				print_error(int error);
int				print_error_token(int error, char *str);
int				check(char *str);
int				check_error(char *str);

/*# Tree #*/
void			get_blocks(t_block *input);
void			put_block(t_block block);
char			*last_operor(char *str, char *small, int len);
char			**get_tab_block(t_block *input);
int				count_block(t_block *input);
int				*get_op(t_block *input, t_list **garb);

/*# COMMANDE CREATION#*/
int				count_token(char *str);
t_token			*tokenization(char *str, int nb_token);
int				init_commande(t_cmd *cmd, char *str, int len, t_context *conte);
char			*find_path(char *command, t_context *context);
int				is_redir(char *str);

/*#REDIRECTION#*/
void			close_fd(t_cmd *cmd);
void			open_redirection(t_token *token, int nb_token, t_cmd *cmd, t_context *context);
int				open_infile(char *file, t_context *context);
int				open_outfile(char *file, t_context *context);
int				open_outfile_extend(char *file, t_context *context);
int				heredoc(char *str, t_context *context);
void			child_exit_status(int res, t_context *context);

char			*expender(char *str, t_context *context);
char			*expend_var(char *str, t_context *context);
int				is_var(char *str);
void			cpy_var(char *s1, char *s2, t_env *env, int *index);

/* ### Execution functions ### */
void			exec_block(t_block *input, t_context *context);


/* ### Builtin functions ### */

int				is_builtin(char *cmd);
unsigned char	exec_builtin(
					t_cmd cmd, t_context *context, int output_fd, int input_fd);

/*
	args : malloc'd array of malloc'd str
*/
typedef int			(*t_builtin_func)(char **args,
			t_context *context, int input_fd, int output_fd);

int				echo_cmd(char **args,
					t_context *context, int input_fd, int output_fd);
int				cd_cmd(char **args,
					t_context *context, int input_fd, int output_fd);
int				pwd_cmd(char **args,
					t_context *context, int input_fd, int output_fd);
int				export_cmd(char **args,
					t_context *context, int input_fd, int output_fd);
int				unset_cmd(char **args,
					t_context *context, int input_fd, int output_fd);
int				env_cmd(char **args,
					t_context *context, int input_fd, int output_fd);
int				exit_cmd(char **args,
					t_context *context, int input_fd, int output_fd);

int				cd(char *path, t_context *context);
void			unset(char *key, t_context *context, int flag);
int				add_export(char *arg, t_context *context);

#endif
