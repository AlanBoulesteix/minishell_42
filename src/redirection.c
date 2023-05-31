
#include "minishell.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int	find_redir(char *str, int *index, int *type)
{
	if (str[0] == '<' && str[1] != '<')
	{
		*type = REDIR_IN;
		(*index)++;
	}
	else if (str[0] == '<' && str[1] == '<')
	{
		*type = HERE_DOC;
		(*index) += 2;
	}
	else if (str[0] == '>' && str[1] != '>')
	{
		*type = REDIR_OUT;
		(*index)++;
	}
	else if (str[0] == '>' && str[1] == '>')
	{
		*type = REDIR_OUT_EXTEND;
		(*index) += 2;
	}
	return (*type);
}


void	open_redir(t_cmd *cmd, char *str, int *i, int type)
{
	int		len_file;
	char	c;

	len_file = 0;
	while(str[*i] && str[*i] == ' ')
		(*i)++;
	while(str[*i + len_file] && str[*i + len_file] != ' ')
		len_file++;
	c = str[*i + len_file];
	str[*i + len_file] = 0;
	if (type == REDIR_IN)
	{
		if(cmd->input_fd > 0 && cmd->input_fd != STDIN_FILENO)
			close(cmd->input_fd);
		cmd->input_fd = open_infile(str + *i);
	}
	else if (type == REDIR_OUT)
	{
		if(cmd->output_fd > 0 && cmd->output_fd != STDOUT_FILENO)
			close(cmd->output_fd);
		cmd->output_fd = open_outfile(str + *i);
	}
	else if (type == REDIR_OUT_EXTEND)
	{
		if(cmd->output_fd > 0 && cmd->output_fd != STDOUT_FILENO)
		close(cmd->output_fd);
		cmd->output_fd = open_outfile_extend(str + *i);
	}
	str[*i + len_file] = c;
}

void	open_redirection(char *str, t_cmd *cmd)
{
	int		i;
	int		type;

	i = 0;
	type = 0;
	cmd->input_fd = STDIN_FILENO;
	cmd->output_fd = STDOUT_FILENO;
	while (str[i])
	{
		if (find_redir(&str[i], &i, &type))
		{
			open_redir(cmd, str, &i, type);
			type = 0;
		}
		i++;
	}
}