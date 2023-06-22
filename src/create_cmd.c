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

//char	*get_src()

//void	tockenize_word(t_block *input, t_vector *tockens, int *i)
//{
//	int		in_simple;
//	int		in_double;
//	t_token	token;

//	in_double = 0;
//	in_simple = 0;
//	token.src = get_src(input, i);
//	//while (!in_double && !in_simple && input->start[*i] != ' ')
//	//{
//	//	if (input->start[*i] == '"')
//	//		in_double = !in_double;
//	//	if (input->start[*i] == '\'')
//	//		in_simple = !in_simple;
//	//	input->start[*i] =
//	//	(*i)++;
//	//}
//}

//t_vector	tockenize(t_block *input, t_context *context)
//{
//	t_vector	tokens;
//	int			i;
//	int			in_word;

//	init_vec(&tokens, sizeof(t_token));
//	i = -1;
//	in_word = 0;
//	while (++i < input->len)
//	{
//		if (input->start[i] == ' ')
//			in_word = 0;
//		else if (!in_word)
//		{
//			in_word = 1;
//			tockenize_word(input, &tokens, &i);
//		}
//	}
//}

t_vector	get_tokens(t_block *input)
{
	t_vector	tokens;
	int			nb_token;

	nb_token = count_token(input->start);
	init_vec(&tokens, sizeof(t_token));
	tokens.tab = tokenization(input->start, nb_token, input->heredoc);
	tokens.len = nb_token;
	tokens.msize = nb_token * sizeof(t_token);
	return (tokens);
}

void	print_token(t_token *token)
{
	printf_fd(STDIN_FILENO,
		"src: {%s} f_str: {%s} type: %d heredoc: %d",
		token->src, token->f_str, token->type, token->heredoc);
}

bool	cmd_is_export(t_vector *ven)
{
	int		i;
	t_token	*token;

	i = -1;
	token = (t_token *)ven->tab;
	while (++i < ven->len)
	{
		if (token[i].type == CMD)
			return (ft_streq(token[i].src, "export"));
	}
	return (false);
}

int	expend_tokens(t_vector *ven, t_context *context)
{
	int		i;
	t_token	*token;
	bool	is_export;

	i = -1;
	token = (t_token *)ven->tab;
	is_export = cmd_is_export(ven);
	while (++i < ven->len)
	{
		if (token[i].type == HERE_DOC)
			token[i].f_str = token[i].src;
		else if (token[i].type & (REDIR_OUT | REDIR_OUT_EXTEND | REDIR_IN))
		{
			token[i].f_str = expend_redir(token[i].src, context);
			if (ft_strchr(token[i].f_str, ' '))
			{
				printf_fd(STDERR_FILENO,
					"minishell: %s : ambiguous redirect", token[i].src);
				context->exit_value = 1;
				return (1);
			}
		}
		else if (is_export)
			token[i].f_str = expend_export(token[i].src, context);
		else
			token[i].f_str = expend_cmd(token[i].src, context);
	}
	return (0);
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
	print_vector(&tokens, (void *)&print_token);
	//ext = expend_var(input->start, context);
	//printf_fd(STDERR_FILENO, "ext: %s\n", ext);
	//token = tokenization(ext, nb_token, input->heredoc);
	//extend_token(token, nb_token, context);
	//open_redirection(token, nb_token, cmd, context);
	//cmd->cmd = get_cmd(token, nb_token);
	//if (is_builtin(cmd->cmd[0]))
	//	cmd->path = NULL;
	//else
	//{
	//	cmd->path = find_path(cmd->cmd[0], context);
	//	add_node(cmd->path);
	//	if (!cmd->path && !context->exit_value)
	//	{
	//		if (cmd->cmd[0])
	//		{
	//			printf_fd(STDERR_FILENO, "%s: command not found\n", cmd->cmd[0]);
	//			context->exit_value = 127;
	//		}
	//		else
	//			context->exit_value = 0;
	//		close_fd(cmd);
	//		return (1);
	//	}
	//	if (context->exit_value)
	//		return (1);
	//}
	return (1);
}
