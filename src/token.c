
#include "minishell.h"

int	count_token(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		while (str[i] == ' ' || is_redir(&str[i]))
			i++;
		if (str[i])
			count ++;
		while (str[i] && str[i] != ' ' && !is_redir(&str[i]))
			i++;
	}
	return (count);
}

int	find_redir2(char *str, int *index, int *type) //@TODO RENAME FUNCTION
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

int	len_to_cpy(char *str)
{
	int i;

	i = 0;
	while (str[i] && str[i] != ' ' && !is_redir(&str[i]))
		i++;
	return (i);
}


char *cpy_str(char *str, int *i)
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
		dup[j] = str[*i];
		(*i)++;
	}
	dup[j] = '\0';
	return (dup);
}


t_token	*tokenization(char *str)
{
	t_token *token;
	int		nb_token;
	int		i;
	int		j;

	nb_token = count_token(str);
	token = my_malloc(sizeof(t_token)*nb_token);
	i = 0;
	j = 0;
	while (str[i])
	{
		while (str[i] && str[i] == ' ')
			i++;
		if (!str[i])
			break ;
		if (is_redir(&str[i]))
		{
			token[j].type = find_redir2(&str[i], &i, &(token[j].type));
			token[j].s_str = cpy_str(str, &i);
		}
		else
		{
			token[j].type = CMD;
			token[j].s_str = cpy_str(str, &i);
		}
		j++;
	}
	return (token);
}