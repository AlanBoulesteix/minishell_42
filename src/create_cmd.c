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

char **get_cmd(t_token *token, int len)
{
	char 	**cmd;
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
	int i;

	i = -1;
	while (++i < nb_token)
		token[i].f_str = expender(token[i].s_str, context);
}

int	init_commande(t_cmd *cmd, char *str, int len, t_context *context)
{
	char	c;
	t_token	*token;
	int		nb_token;

	c = str[len];
	str[len] = 0;
	nb_token = count_token(str);
	token = tokenization(str, nb_token);
	extend_token(token, nb_token, context);
	open_redirection(token, nb_token, cmd);
	cmd->cmd = get_cmd(token, nb_token);
	str[len] = c;
	if (is_builtin(cmd->cmd[0]))
		cmd->path = NULL;
	else
	{
		context->exit_value = 0;
		cmd->path = find_path(cmd->cmd[0], context);
		add_node(cmd->path);
		if (!cmd->path && !context->exit_value)
		{
			printf_fd(STDERR_FILENO, "%s: command not found\n", cmd->cmd[0]);
			context->exit_value = 127;
		}
		if (context->exit_value)
			return (1);
	}
	return (1);
}
