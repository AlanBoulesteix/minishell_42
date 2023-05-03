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


int	*define_type(char **input, t_list **garbage)
{
	int *type;
	int	i;

	i = 0;
	while (input[i])
		i++;
	type = my_malloc(sizeof(int) * i, garbage);
	i = -1;
	while (input[++i])
	{
		if (input[i][0] == '<' || input[i][0] == '>')
			type[i] = REDIR;
		else if (input[i][0] == '|')
			type[i] = PIPE;
		else if (i > 0 && (type[i - 1] == CMD || type[i - 1] == ARG))
			type[i] = ARG;
		else if (i > 0 && type[i - 1] == REDIR)
			type[i] = FILES;
		else
			type[i] = CMD;
	}
	return (type);
}

char *my_dup(char *str, t_list **garbage)
{
	int 	i;
	char	*dup;

	i = -1;
	dup = my_malloc(sizeof(char) * (ft_strlen(str) + 1), garbage);
	while (str[++i])
		dup[i] = str[i];
	dup[i] = '\0';
	return (dup);
}

t_token	*init_token(char *content, int type, t_list **garbage)
{
	t_token	*node;

	node = my_malloc(sizeof(t_token), garbage);
	node->content = my_dup(content, garbage);
	node->next = NULL;
	node->type = type;
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
