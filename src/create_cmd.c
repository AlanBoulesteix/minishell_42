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

//char	*get_s_str()

//void	tockenize_word(t_block *input, t_vector *tockens, int *i)
//{
//	int		in_simple;
//	int		in_double;
//	t_token	token;

//	in_double = 0;
//	in_simple = 0;
//	token.s_str = get_s_str(input, i);
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
		"s_str: {%s} f_str: {%s} type: %d heredoc: %d",
		token->s_str, token->f_str, token->type, token->heredoc);
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
