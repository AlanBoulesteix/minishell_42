
#include "minishell.h"

char	*variable_find(char *str, int *index)
{
	char	*dup;
	int		i;
	int		j;

	i = 0;
	j = -1;
	while (str[i] && str[i] != ' ' && str[i] != '\'' && str[i] != '\"')
		i++;
	dup = my_malloc(sizeof(char) * (i + 1));
	while (++j < i)
		dup[j] = str[j];
	dup[j] = '\0';
	*index += i;
	return (dup);

}

int	is_var(char *str)
{
	if (str[0] == '$' && str[1] && str[1] != ' ')
	{
		if (str[1] == '\"' && (str[2] == ' ' || str[2] == '\0'))
			return (0); // @TODO ? verif
		return (1);
	}
	return (0);
}

int	nb_char(char *str, t_context *context)
{
	int		i;
	int		nb_char;
	bool	in_simple;
	bool	in_double;
	char	*var;

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
				var = get_env_value(&context->env, variable_find(str + i, &i));
				if (var)
				{
					nb_char += ft_strlen(var);
					while (str[i] && str[i] != ' ' && str[i] != '\'' && str[i] != '\"')
						i++;
				}
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

void	cpy_var(char *s1, char *s2, t_env *env, int *index)
{
	int		j;
	int		i;
	char	*var;

	i = 0;
	j = 0;
	var = get_env_value(env, variable_find(s2 + i, &i));
	if (!var)
		return ;
	while (var[j])
	{
		s1[*index] = var[j];
		(*index)++;
		j++;
	}
}

char	*expender(char *str, t_context *context)
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
				while (str[i] && str[i] != ' '
					&& str[i] != '\'' && str[i] != '\"')
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
