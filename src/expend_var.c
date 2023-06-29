
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

int	is_export(char *str)
{
	return (ft_strlen(str) >= 6 && str[0] == 'e'
		&& str[1] == 'x' && str[2] == 'p'
		&& str[3] == 'o' && str[4] == 'r' && str[5] == 't'
		&& (str[6] == ' ' || str[6] == '\0' || str[6] == '\t'
			|| str[6] == '>' || str[6] == '<'));
}

int	len_export(char *str)
{
	int		i;
	bool	in_simple;
	bool	in_double;

	i = 0;
	in_simple = false;
	in_double = false;
	while (str[i] && str[i] == ' ')
		i++;
	while (str[i] && (str[i] != ' ' || in_double || in_simple))
	{
		if (str[i] && str[i] == '\'' && !in_double)
			in_simple = !in_simple;
		if (str[i] && str[i] == '\"' && !in_simple)
			in_double = !in_double;
		i++;
	}
	return (i + 6);
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

void	cpy_export(char *expens, char *str, int *i, int *j)
{
	int	len;
	int	index;

	len = len_export(str + 6);
	index = -1;
	while (++index < len)
	{
		expens[*j] = str[index];
		(*j)++;
	}
	*i += index;
}
