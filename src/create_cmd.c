#include "minishell.h"

int	nb_word(char *str)
{
	int	i;
	int count;
	
	enum {CMD, NOT_CMD} type = CMD;
	count = 0;
	i = 0;
	while (str[i])
	{
		while (str[i] == ' ')
			i++;
		if (!str[i])
			break;
		if (is_redir(&str[i]))
			type = NOT_CMD;
		else
			type = CMD;
		if (type == CMD)
		{
			count ++;
			while (str[i] && str[i] != '<' && str[i] != '>' && str[i] != ' ')
				i++;
		}
		else
		{
			i++;
			while (str[i] == ' ')
				i++;
			while (str[i] && str[i] != ' ')
				i++;
		}
	}
	return (count);
}

char	*cpy_word(char *str, int len) //@todo expend $VAR and Quotes
{
	int		i;
	int		j;
	char	*dup;
	bool	in_simple;
	bool	in_double;

	i = 0;
	j = 0;
	in_simple = false;
	in_double = false;
	dup = my_malloc(sizeof(char) * (len + 1));
	while (str[i] && i < len)
	{
		if (str[i] == '\'' && !in_double)
		{
			in_simple = !in_simple;
		}
		else if (str[i] == '\"' && !in_simple)
		{
		 	in_double = !in_double;
		}
		else
		{
	  		dup[j] = str[i];
			j++;
		}
	 	i++;

	}
	dup[j] = '\0';
	return (dup);
}

char **get_cmd(char *str, int len)
{
	char	**tab;
	int		i;
	int		j;
	int		len_to_cpy;

	enum {CMD, NOT_CMD} type = CMD;
	tab = my_malloc(sizeof(char*) * (nb_word(str) + 1));
	printf("nb word = %d\n", nb_word(str));
	i = 0;
	j = 0;
	len_to_cpy = 0;
	while (i < len)
	{
		while (str[i] == ' ')
			i++;
		if (i >= len)
			break;
		if (is_redir(&str[i]))
			type = NOT_CMD;
		else
			type = CMD;
		if (type == CMD)
		{
			while (str[i + len_to_cpy] && str[i + len_to_cpy] != '<' && str[i + len_to_cpy] != '>' && str[i + len_to_cpy] != ' ')
				len_to_cpy++;
			tab[j] = cpy_word(str + i, len_to_cpy);
			j++;
			i += len_to_cpy;
		}
		else
		{
			i++;
			while (str[i] == ' ')
				i++;
			while (str[i] && str[i] != ' ')
				i++;
		}
	}
	tab[j] = NULL;
	return (tab);
}

int	init_commande(t_cmd *cmd, char *str, int len, t_env *env)
{
	cmd->cmd = get_cmd(str, len);
	cmd->path = find_path(cmd->cmd[0], env);
	add_node(cmd->path);
	cmd->input_fd = -1;
	cmd->output_fd = -1;
	return (0);
}