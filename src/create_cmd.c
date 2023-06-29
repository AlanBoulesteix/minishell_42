/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulest <aboulest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 17:00:24 by aboulest          #+#    #+#             */
/*   Updated: 2023/06/29 18:01:46 by aboulest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	print_token(t_token *token) //@TODO delete
// {
// 	printf_fd(STDIN_FILENO,
// 		"src: {%s} f_str: {%s} type: %d heredoc: %d, state: %d",
// 		token->src, token->f_str, token->type, token->heredoc, token->state);
// }

int			nb_arg(t_token *token, int len);
char		**get_cmd(t_token *token, int len);
t_vector	get_tokens(t_block *input);
bool		cmd_is_export(t_vector *vec);
void		remove_dead_token(t_vector *vec);

int	expend_token_loop(t_vector *vec, int i,
	bool is_export, t_context *context)
{
	char	*ext;

	if (((t_token *)vec->tab)[i].state == DEFAULT)
	{
		if (((t_token *)vec->tab)[i].type == HERE_DOC)
			((t_token *)vec->tab)[i].f_str = ((t_token *)vec->tab)[i].src;
		else if (((t_token *)vec->tab)[i].type &
			(REDIR_OUT | REDIR_OUT_EXTEND | REDIR_IN))
		{
			if (expend_redir((&((t_token *)vec->tab)[i]), vec, i, context))
				return (1);
		}
		else if (is_export)
			((t_token *)vec->tab)[i].f_str = expend_export(
					((t_token *)vec->tab)[i].src, vec, i, context);
		else
		{
			ext = expend_default(((t_token *)vec->tab)[i].src, vec, i, context);
			((t_token *)vec->tab)[i].f_str = ext;
		}
	}
	return (0);
}

int	expend_tokens(t_vector *vec, t_context *context)
{
	int		i;
	bool	is_export;

	i = -1;
	is_export = cmd_is_export(vec);
	while (++i < vec->len)
		if (expend_token_loop(vec, i, is_export, context))
			return (1);
	return (0);
}

int	fulfill_cmd_path(t_cmd *cmd, t_context *context)
{
	if (is_builtin(cmd->cmd[0]))
		cmd->path = NULL;
	else
	{
		cmd->path = find_path(cmd->cmd[0], context);
		add_node_ignore_null(cmd->path);
		if (!cmd->path && !context->exit_value)
		{
			if (cmd->cmd[0])
			{
				printf_fd(STDERR_FILENO, "minishell: %s: command not found\n",
					cmd->cmd[0]);
				context->exit_value = 127;
			}
			else
				context->exit_value = 0;
			close_fd(cmd);
			return (1);
		}
		if (context->exit_value)
			return (1);
	}
	return (0);
}

int	init_commande(t_cmd *cmd, t_block *input, t_context *context)
{
	char		c;
	t_vector	tokens;

	context->old_exit_value = context->exit_value;
	context->exit_value = 0;
	c = input->start[input->len];
	input->start[input->len] = 0;
	tokens = get_tokens(input);
	if (expend_tokens(&tokens, context))
		return (1);
	input->start[input->len] = c;
	remove_dead_token(&tokens);
	if (!tokens.len)
		return (1);
	open_redirection(tokens.tab, tokens.len, cmd, context);
	if (cmd->input_fd == -1 || cmd->output_fd == -1)
		return (1);
	cmd->cmd = get_cmd(tokens.tab, tokens.len);
	if (fulfill_cmd_path(cmd, context))
		return (1);
	return (0);
}
