
#include "minishell.h"

int	is_var(char *str)
{
	if (str[0] == '$' && (ft_isalnum(str[1]) || str[1] == '_' || str[1] == '\"' || str[1] == '?'))
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

void	cpy_var(char *s1, char *s2, t_env *env, int *index)
{
	int		i;
	char	*var;
	char	c;

	i = 0;
	while (ft_isalnum(s2[i]) || s2[i] == '_')
		i++;
	c = s2[i];
	s2[i] = 0;
	var = get_env_value(env, s2);
	s2[i] = c;
	i = 0;
	if (!var)
		return ;
	while (var[i])
	{
		s1[*index] = var[i];
		(*index)++;
		i++;
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
	printf("str = %s\n", str);
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
