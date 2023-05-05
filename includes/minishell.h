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

#include <stdio.h>
#include "../libft/libft.h"
#include <stdbool.h> 

#define UNDEFINE -1
#define NO_OP 0
#define PP 1
#define OR 2
#define AND 3

typedef struct s_context
{
	char	*input;
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

int	init_context(t_context *context);

int	ft_streq(char *str1, char *str2);

void	get_blocks(t_block *input, t_list **garbage);
char	*last_operor(char *str, char *small, int len);

/*##### MALLOC CHAINE ########*/
void	*my_malloc(size_t size, t_list **garbage);
void	free_all(t_list **garbage);
void	free_node(void *add, t_list **garbage);

#endif
