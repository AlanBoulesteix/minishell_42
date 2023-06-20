#include "minishell.h"

int	nb_arg(t_token *token, int len)
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	while (++i < len)
	{
		if (token[i].type == CMD)
			count++;
	}
	return (count);
}

char	**get_cmd(t_token *token, int len)
{
	char	**cmd;
	int		i;
	int		j;

	cmd = my_malloc(sizeof(char *) * (nb_arg(token, len) + 1));
	i = -1;
	j = 0;
	while (++i < len)
	{
		if (token[i].type == CMD)
		{
			cmd[j] = token[i].f_str;
			j++;
		}
	}
	cmd[j] = NULL;
	return (cmd);
}

void	extend_token(t_token *token, int nb_token, t_context *context)
{
	int	i;

	i = -1;
	while (++i < nb_token)
		token[i].f_str = expender(token[i].s_str, context);
}

int	init_commande(t_cmd *cmd, t_block *input, t_context *context)
{
	char	c;
	char	*ext;
	t_token	*token;
	int		nb_token;

	c = input->start[input->len];
	input->start[input->len] = 0;
	ext = expend_var(input->start, context);
	nb_token = count_token(ext);
	token = tokenization(ext, nb_token, input->heredoc);
	extend_token(token, nb_token, context);
	context->exit_value = 0;
	open_redirection(token, nb_token, cmd, context);
	cmd->cmd = get_cmd(token, nb_token);
	input->start[input->len] = c;
	if (is_builtin(cmd->cmd[0]))
		cmd->path = NULL;
	else
	{
		cmd->path = find_path(cmd->cmd[0], context);
		add_node(cmd->path);
		if (!cmd->path && !context->exit_value)
		{
			if (cmd->cmd[0])
			{
				printf_fd(STDERR_FILENO, "%s: command not found\n", cmd->cmd[0]);
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
