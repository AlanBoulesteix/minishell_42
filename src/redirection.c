/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulest <aboulest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 16:23:13 by vlepille          #+#    #+#             */
/*   Updated: 2023/06/30 15:02:17 by aboulest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

void	open_files(t_token token, t_cmd *cmd, t_context *context)
{
	int	precedent_fd;

	if (token.type == REDIR_IN || token.type == HERE_DOC)
		precedent_fd = cmd->input_fd;
	else
		precedent_fd = cmd->output_fd;
	if (token.type == REDIR_IN)
		cmd->input_fd = open_infile(token.f_str, context);
	else if (token.type == REDIR_OUT)
		cmd->output_fd = open_outfile(token.f_str, context);
	else if (token.type == REDIR_OUT_EXTEND)
		cmd->output_fd = open_outfile_extend(token.f_str, context);
	else if (token.type == HERE_DOC)
		cmd->input_fd = token.heredoc;
	if (precedent_fd > 2 && precedent_fd != token.heredoc)
		close(precedent_fd);
}

void	open_redirection(
	t_token *token, int nb_token, t_cmd *cmd, t_context *context)
{
	int	i;

	i = -1;
	cmd->input_fd = STDIN_FILENO;
	cmd->output_fd = STDOUT_FILENO;
	while (++i < nb_token)
	{
		if (token[i].type != CMD && !context->exit_value)
			open_files(token[i], cmd, context);
	}
	if (token[0].heredoc != -1 && cmd->input_fd != token[0].heredoc)
		close(token[0].heredoc);
}
