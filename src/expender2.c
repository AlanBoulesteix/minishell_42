
#include "minishell.h"

int	len_cpy(char *str)
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


int expend_size(char *str, t_context *context)
{
	int		i;
	int		j;
	int		count;
	bool	in_simple;
	bool	in_double;
	char	c;
	char	*var;

	i = 0;
	in_simple = false;
	in_double = false;
	count = 0;
	while (str[i])
	{
		if (str[i] == '\'' && !in_double)
		{
			in_simple = !in_simple;
			i++;
			count++;
		}
		else if (str[i] == '\"' && !in_simple)
		{
			in_double = !in_double;
			i++;
			count++;
		}
		else if ((str[i] == '<' || str[i] == '>') && !in_simple && !in_double)
		{
			j = len_cpy(str + i);
			i += j;
			count += j;
		}
		else if (is_var(&str[i]) && !in_simple)
		{
			i++;
			if (str[i] == '?' && i++)
				count += nbrlen(context->exit_value);
			else if (ft_isdigit(str[i]))
			{
				if (str[i] - '0' < context->argc)
					count += ft_strlen(context->argv[(str[i] - '0')]);
				i++;
			}
			else
			{
				j = i;
				while (ft_isalnum(str[j]) || str[j] == '_')
					j++;
				c = str[j];
				str[j] = 0;
				var = get_env_value(&context->env, &str[i]);
				str[j] = c;
				if (var)
					count += ft_strlen(var);
			}
		}
		else
		{
			count++;
			i++;
		}
	}
	return (count);
}

void	cpy_redir(char *expens, char *str, int *i, int *j)
{
	int	len;
	int	index;

	len = len_cpy(str);
	index = -1;
	while (++index < len)
	{
		expens[*j] = str[index];
		(*j)++;
	}
	*i += index;
}

void	cpy_arg(char *expens, char *str, int *j)
{
	int	i;

	i = 0;
	while (str[i])
	{
		expens[*j] = str[i];
		i++;
		(*j)++;
	}
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
	expens = my_malloc(sizeof(char) * (expend_size(str, context) + 1)); 
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
			else if (ft_isdigit(str[i]))
			{
				if (str[i] - '0' < context->argc)
					cpy_arg(expens, context->argv[str[i] - '0'], &j);
				i++;
			}
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