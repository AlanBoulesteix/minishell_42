
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

