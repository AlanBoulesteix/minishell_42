
#include "minishell.h"

char	*variable_find(char *str, int *index)
{
	char *dup;
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

int     nb_char(char *str, t_env *env)
{
    int i;
    int nb_char;
    bool    in_simple;
    bool    in_double;
	char	*var;

    i = 0;
    in_simple = false;
    in_double = false;
    nb_char = 0;
    while(str[i])
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
        else if (str[i] == '$' && !in_simple)
        {
            i++;
			var = get_env_value(env, variable_find(str + i, &i));
			if (var)
			{
				nb_char += ft_strlen(var);
				while (str[i] && str[i] != ' ')
					i++;
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

void    cpy_var(char *s1, char *s2, t_env *env, int *index)
{
    int  j;
    int  i;
    char *var;

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
/*Quand $VAR EXISTE PAS A CORRIGER*/
char    *expender(char *str, t_env *env)
{
    int i;
    int j;
    char *expens;
    bool    in_simple;
    bool    in_double;

    i = 0;
    j = 0;
    in_simple = false;
    in_double = false;
    expens = my_malloc(sizeof(char) * (nb_char(str, env) + 1));
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
        else if (str[i] == '$' && !in_simple)
        {
            i++;
            cpy_var(expens, str + i, env, &j);
            while (str[i] && str[i] != ' ')
                i++;
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
