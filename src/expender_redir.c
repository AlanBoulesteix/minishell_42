#include "minishell.h"

static int	nb_char(char *str, t_context *context)
{
	int		i;
	int		j;
	int		nb_char;
	bool	in_simple;
	bool	in_double;
	char	*var;
	char	c;

	i = 0;
	in_simple = false;
	in_double = false;
	nb_char = 0;
	while (str[i])
	{
		if (str[i] == '\'' && !in_double)
		{
			in_simple = !in_simple;
			i++;
		}
		else if (str[i] == '\"' && !in_simple)
		{
			in_double = !in_double;
			i++;
		}
		else if (is_var(&str[i]) && !in_simple)
		{
			i++;
			if (str[i] == '?')
				nb_char += nbrlen(context->exit_value);
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
					nb_char += ft_strlen(var);
			}
		}
		else
		{
			i++;
			nb_char ++;
		}
	}
	return (nb_char);
}

char	*expender_redir(char *str, t_context *context)
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
	expens = my_malloc(sizeof(char) * (nb_char(str, context) + 1));
	while (str[i])
	{
		if (str[i] == '\'' && !in_double)
		{
			in_simple = !in_simple;
			i++;
		}
		else if (str[i] == '\"' && !in_simple)
		{
			in_double = !in_double;
			i++;
		}
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
