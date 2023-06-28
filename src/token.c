#include "minishell.h"

int	count_token(char *str)
{
	int		i;
	int		count;
	bool	in_simple;
	bool	in_double;

	i = 0;
	count = 0;
	in_simple = false;
	in_double = false;
	while (str[i])
	{
		while (str[i] == ' ' || is_redir(&str[i]))
			i++;
		if (str[i])
			count ++;
		while (str[i] && (str[i] != ' ' || in_simple || in_double) && (!is_redir(&str[i]) || in_simple || in_double))
		{
			if (str[i] == '\'' && !in_double)
				in_simple = !in_simple;
			if (str[i] == '\"' && !in_simple)
				in_double = !in_double;
			i++;
		}
	}
	return (count);
}

void	find_redir(char *str, int *index, int *type)
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
}

int	len_to_cpy(char *str)
{
	int 	i;
	bool	in_simple;
	bool	in_double;

	i = 0;
	in_simple = false;
	in_double = false;
	while (str[i])
	{
		if (str[i] == '\'' && !in_double)
			in_simple = !in_simple;
		if (str[i] == '\"' && !in_simple)
			in_double = !in_double;
		if (is_redir(&str[i]) && !in_simple && !in_double)
			break ;
		if (str[i] == ' ' && !in_simple && !in_double)
			break ;
		i++;
	}
	return (i);
}


char	*cpy_str(char *str, int *i, bool *in_simple, bool *in_double)
{
	char	*dup;
	int		len;
	int		j;


	while (str[*i] == ' ')
		(*i)++;
	len = len_to_cpy(str + (*i));
	dup = my_malloc(sizeof(char) * (len +1));
	j = -1;
	while (++j < len)
	{
		if (str[*i] == '\'' && !(*in_double) && *in_simple)
			*in_simple = !(*in_simple);
		if (str[*i] == '\"' && !(*in_simple) && *in_double)
			*in_double = !(*in_double);
		dup[j] = str[*i];
		(*i)++;
	}
	dup[j] = '\0';
	return (dup);
}


t_token	*tokenization(char *str, int nb_token, int heredoc)
{
	t_token	*token;
	int		i;
	int		j;
	bool	in_simple;
	bool	in_double;

	token = my_malloc(sizeof(t_token) * nb_token);
	i = 0;
	j = 0;
	in_simple = false;
	in_double = false;
	while (str[i])
	{
		while (str[i] && str[i] == ' ')
			i++;
		if (!str[i])
			break ;
		if (str[i] == '\'' && !in_double)
			in_simple = !in_simple;
		if (str[i] == '\"' && !in_simple)
			in_double = !in_double;
		if (is_redir(&str[i]) && !in_double && !in_simple)
		{

			find_redir(&str[i], &i, &(token[j].type));
			token[j].src = cpy_str(str, &i, &in_simple, &in_double);
			token[j].heredoc = heredoc;
			token[j].f_str = NULL;
			token[j].state = DEFAULT;
		}
		else
		{
			token[j].type = CMD;
			token[j].src = cpy_str(str, &i, &in_simple, &in_double);
			token[j].heredoc = heredoc;
			token[j].f_str = NULL;
			token[j].state = DEFAULT;
		}
		j++;
	}
	return (token);
}