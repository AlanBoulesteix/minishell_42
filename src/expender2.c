
#include "minishell.h"

int	len_to_cpy2(char *str)
{
	int 	i;
	bool	in_simple;
	bool	in_double;
	i = 0;
	i++;
	in_simple = false;
	in_double = false;
	if (str[0] == str[1])
		i++;
	while (str[i] == ' ')
		i++;
	while (str[i] && (str[i] != ' ' || in_double || in_simple))
	{
		if (str[i] && str[i] == '\'' && !in_double)
			in_simple = !in_simple;
		if (str[i] && str[i] == '\"' && !in_simple)
			in_double = !in_double;
		i++;
	}
	return (i);
}

void	cpy_redir(char *expens, char *str, int *i, int *j)
{
	int	len;
	int	index;

	len = len_to_cpy2(str);
	index = -1;
	while (++index < len)
	{
		expens[*j] = str[index];
		(*j)++;
	}
	*i += index;
}


char *expend_var(char *str, t_context *context)
{
	int		i;
	int		j;
	char	*expens;
	bool	in_simple;
	bool	in_double;

	i = 0;
	j = 0;
	in_simple = false;
	in_double = false;
	expens = my_malloc(10000);
	while (str[i])
	{
		if (str[i] == '\'' && !in_double)
			in_simple = !in_simple;
		if (str[i] == '\"' && !in_simple)
			in_double = !in_double;
		if ((str[i] == '<' || str[i] == '>') && !in_simple && !in_double)
			cpy_redir(expens, str + i, &i, &j);
		else if (is_var(&str[i]) && !in_simple)
		{
			i++;
			if (str[i] == '?' && i++)
				cpy_nbr(expens, context->exit_value, &j);
			else
			{
				cpy_var(expens, str + i, &context->env, &j);
				while (ft_isalnum(str[i]) || str[i] == '_')
					i++;
			}
		}
		else
		{
			expens[j] = str[i];
			i++;
			j++;
		}
	}
	expens[j] = '\0';
	return (expens);
}