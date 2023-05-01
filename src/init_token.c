/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulest <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 13:13:46 by aboulest          #+#    #+#             */
/*   Updated: 2023/05/01 14:47:57 by aboulest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	define_type(char *content)
{
	if (content[0] == '-')
		return (OPT);
	else if (content[0] == '|')
		return (PIPE);
	else if (content[0] == '<' || content[0] == '>')
		return (REDIR);
	else if (access(content, X_OK) == 1)
	{
		if (access(content, F_OK) == 0)
			return (FILES);
		else
			return (CMD);
	}
	else
		return (CMD);
}

t_token	*init_token(char *content)
{
	t_token	*node;

	node = malloc(sizeof(node));
	if (!node)
		return (NULL);
	node->content = content;
	node->next = NULL;
	node->type = define_type(content);
	return (node);
}

t_token	*last_token(t_token *token)
{
	t_token *tmp;

	if (!token)
		return (NULL);
	else
	{
		tmp = token;
		while (tmp->next)
			tmp = tmp->next;
	}
	return (tmp);
}

void	token_addbck(t_token **token, t_token *node)
{
	if (*token)
		(last_token(*token))->next = node;
	else
		*token = node;
}
