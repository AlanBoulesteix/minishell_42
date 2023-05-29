/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlepille <vlepille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 11:59:20 by aboulest          #+#    #+#             */
/*   Updated: 2023/05/16 17:47:43 by vlepille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include "libft.h"
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

# define WORD 1
# define OPE 2
# define PARENTHESIS 4
# define REDIR 8
# define NEWLINE 16

typedef t_vector	t_env;

typedef struct s_context
{
	char	*input;
	t_env	env;
	// t_list	*garb;
}	t_context;

typedef struct s_block
{
	char			*start;
	int				len;
	int				op;
	struct s_block	*left;
	struct s_block	*right;
}	t_block;

typedef struct s_cmd
{
	char	*path;
	char	**cmd;
	int		input_fd; // @TODO ? use fd or filename
	int		output_fd;
}	t_cmd;

/* ### Utils ### */
void	error(int errno, int line);
void	*my_malloc(size_t size);
void	free_all(t_list **garbage);
void	free_node(void *add);
void	add_node(void *ptr);

/* ### Context functions ### */
int		init_context(t_context *context, char **envp);
int		ft_streq(char *str1, char *str2);

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

/* ### Binary tree creation ### */
int		ft_streq(char *str1, char *str2);

/*# ERROR TOKENS #*/
int		is_token(char *str);
void	skip(char *str, int *i);
int		check_token(char *str);
int		print_error(int error);
int		print_error_token(int error, char *str);
int		check(char *str);
int		check_error(char *str);

/*# TREE FUNCTIONS #*/
void	get_blocks(t_block *input);
void	put_block(t_block block);
char	*last_operor(char *str, char *small, int len);
char	**get_tab_block(t_block *input);
int		count_block(t_block *input);
int		*get_op(t_block *input, t_list **garb);

/*# COMMANDE CREATION#*/
int		init_commande(t_cmd *cmd, char *str, int len, t_env *env);
char	*find_path(char *command, t_env *env);
int		is_redir(char *str);

char    *expender(char *str, t_env *env);

/* ### Execution functions ### */
int		exec_block(t_block *input, t_context *context);

#endif
