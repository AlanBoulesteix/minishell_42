/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulest <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 11:59:20 by aboulest          #+#    #+#             */
/*   Updated: 2023/05/01 14:33:47 by aboulest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include "../libft/libft.h"


typedef struct s_context
{
	char	*input;
}	t_context;

typedef enum	s_type
{
	CMD,
	OPT,
	ARG,
	FILES,
	REDIR,
	PIPE,

}	t_type;

typedef struct s_token
{
	char			*content;
	int				type;
	struct s_token	*next;
}				t_token;

int	init_context(t_context *context);

int	ft_streq(char *str1, char *str2);

t_token	*init_token(char *content, t_list **garb);
t_token	*last_token(t_token *token);
void	token_addbck(t_token **token, t_token *node);

void	*my_malloc(size_t size, t_list **garbage);
void	free_all(t_list **garbage);
#endif
