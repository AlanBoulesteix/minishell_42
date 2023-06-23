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

t_vector	get_tokens(t_block *input)
{
	t_vector	tokens;
	int			nb_token;

	nb_token = count_token(input->start);
	init_vec(&tokens, sizeof(t_token));
	tokens.tab = tokenization(input->start, nb_token, input->heredoc);
	tokens.len = nb_token;
	tokens.msize = nb_token;
	return (tokens);
}

void	print_token(t_token *token) //@TODO delete
{
	printf_fd(STDIN_FILENO,
		"src: {%s} f_str: {%s} type: %d heredoc: %d, state: %d",
		token->src, token->f_str, token->type, token->heredoc, token->state);
}

bool	cmd_is_export(t_vector *vec)
{
	int		i;
	t_token	*token;

	i = -1;
	token = (t_token *)vec->tab;
	while (++i < vec->len)
	{
		if (token[i].type == CMD)
			return (ft_streq(token[i].src, "export"));
	}
	return (false);
}

int	expend_tokens(t_vector *vec, t_context *context)
{
	int		i;
	bool	is_export;

	i = -1;
	is_export = cmd_is_export(vec);
	while (++i < vec->len)
	{
		if (((t_token *)vec->tab)[i].state == DEFAULT)
		{
			if (((t_token *)vec->tab)[i].type == HERE_DOC)
				((t_token *)vec->tab)[i].f_str = ((t_token *)vec->tab)[i].src;
			else if (((t_token *)vec->tab)[i].type & (REDIR_OUT | REDIR_OUT_EXTEND | REDIR_IN))
			{
				if (expend_redir((&((t_token *)vec->tab)[i]), vec, i, context))
					return (1);
			}
			else if (is_export)
				((t_token *)vec->tab)[i].f_str = expend_export(((t_token *)vec->tab)[i].src, vec, i, context);
			else
				((t_token *)vec->tab)[i].f_str = expend_default(((t_token *)vec->tab)[i].src, vec, i, context);
		}
	}
	return (0);
}

void	remove_dead_token(t_vector *vec)
{
	int	i;

	i = 0;
	while (i < vec->len)
	{
		if (((t_token *)vec->tab)[i].state == DEAD)
		{
			free_node(((t_token *)vec->tab)[i].f_str);
			free_node(((t_token *)vec->tab)[i].src);
			remove_vec(vec, i);
		}
		else
			i++;
	}
}

int	init_commande(t_cmd *cmd, t_block *input, t_context *context)
{
	char		c;
	//char		*ext;
	t_vector	tokens;

	(void)cmd;
	context->old_exit_value = context->exit_value;
	context->exit_value = 0;
	c = input->start[input->len];
	input->start[input->len] = 0;
	tokens = get_tokens(input);
	if (expend_tokens(&tokens, context))
		return (1); // @TODO ? free tokens
	input->start[input->len] = c;
	//print_vector(&tokens, (void *)&print_token);
	remove_dead_token(&tokens);
	//print_vector(&tokens, (void *)&print_token);
	open_redirection(tokens.tab, tokens.len, cmd, context);
	if (cmd->input_fd == -1 || cmd->output_fd == -1)
		return (1);
	cmd->cmd = get_cmd(tokens.tab, tokens.len); // @TODO free token but carefull : cmd is a pointer to token
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
