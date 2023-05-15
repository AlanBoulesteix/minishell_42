/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulest <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 11:59:20 by aboulest          #+#    #+#             */
/*   Updated: 2023/05/03 14:55:55 by aboulest         ###   ########.fr       */
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

# define MALLOC_FAIL_ERRNO 1
# define OTHER_ERRNO 2

typedef t_vector	t_env;

typedef struct s_context
{
	char	*input;
	t_env	env;
	int		nb_cmd; 		//todo ?
}	t_context;


typedef struct s_block
{
	char			*start;
	int				len;
	int				op;
	struct s_block	*left;
	struct s_block	*right;
}	t_block;

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

/*########ERROR TOKENS##########*/
int		print_error_token(int error);
int		check(char *str);

/*######### TREE FUNCTION ############*/
void	get_blocks(t_block *input, t_list **garbage);
void	put_block(t_block block);
char	*last_operor(char *str, char *small, int len);
char	**get_tab_block(t_block *input, t_list **garb);
int		count_block(t_block *input);
int		*get_op(t_block *input, t_list **garb);

/*##### MALLOC CHAINE ########*/
void	*my_malloc(size_t size, t_list **garbage);
void	free_all(t_list **garbage);
void	free_node(void *add, t_list **garbage);

#endif
