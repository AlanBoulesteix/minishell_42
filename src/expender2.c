
#include "minishell.h"


char *expend_var(char *str, t_context *context)
{
	int		i;
	int		j;
	char	*expens;
	bool	in_simple;
	bool	in_double;
	bool	in_redir;

	i = 0;
	j = 0;
	in_simple = false;
	in_double = false;
	in_redir = false;
	expens = my_malloc(/*SIZE OF LA STRING + la longueur de la VAR*/);
	while (str[i])
	{
		if (str[i] == '\'' && !in_double)
			in_simple = !in_simple;
		if (str[i] == '\"' && !in_simple)
			in_double = !in_double;
		if ((str[i] == '<' || str[i] == '>') && !in_simple && !in_double)
		{
			expens[j] = str[i];
			i++;
			j++;
			
		}
	}	
}