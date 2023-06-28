
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
	if (precedent_fd > 2)
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
}

int	is_metachar(char c)
{
	return (c == ' ' || c == '&' || c == '|' || c == '<'
		|| c == '>' || c == '\t');
}

void	close_and_remove(int fd, t_vector *fds_open)
{
	int	i;

	close(fd);
	i = 0;
	while (i < fds_open->len)
	{
		if (((int *)fds_open->tab)[i] == fd)
			return (remove_vec(fds_open, i));
		i++;
	}
}

void	close_fds_open(t_vector *fds_open)
{
	while (fds_open->len > 0)
	{
		close(((int *)fds_open->tab)[0]);
		remove_vec(fds_open, 0);
	}
}

void	close_fds_open_except(t_vector *fds_open, int except)
{
	int	i;

	i = 0;
	while (fds_open->len > 1)
	{
		if (((int *)fds_open->tab)[0] == except)
			i = 1;
		close(((int *)fds_open->tab)[i]);
		remove_vec(fds_open, i);
	}
}

void	open_heredoc(t_block *block, t_context *context)
{
	int		i;
	int		j;
	char	c;
	bool	in_simple;
	bool	in_double;

	i = 0;
	in_simple = false;
	in_double = false;
	while (i < block->len)
	{
		if (block->start[i] == '\'' && !in_double)
			in_simple = !in_simple;
		else if (block->start[i] == '\"' && !in_simple)
			in_double = !in_double;
		else if (block->start[i] == '<' && block->start[i + 1] == '<' && !in_simple && !in_double)
		{
			j = 0;
			i += 2;
			while (block->start[i] == ' ' && !in_simple && !in_double)
				i++;
			while (block->start[i + j] && (!is_metachar(block->start[i + j]) || in_simple || in_double))
			{
				if (block->start[i + j] == '\'' && !in_double)
					in_simple = !in_simple;
				if (block->start[i + j] == '\"' && !in_simple)
					in_double = !in_double;
				j++;
			}
			c = block->start[i + j];
			block->start[i + j] = 0;
			if (block->heredoc != -1)
				close_and_remove(block->heredoc, &context->fds_open);
			block->heredoc = heredoc((block->start) + i, context);
			block->start[i + j] = c;
			i += j - 1;
		}
		i++;
	}
}