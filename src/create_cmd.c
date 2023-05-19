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

char	*cpy_word(char *str, int len, t_list **garb) //@todo expend $VAR and Quotes
{
	int		i;
	char	*dup;
	
	i = -1;
	dup = my_malloc(sizeof(char) * (len + 1), garb);
	while (++i < len)
		dup[i] = str[i];
	dup[i] = '\0';
	return (dup);
}

char **get_cmd(char *str, int len, t_list **garb)
{
	char	**tab;
	int		i;
	int		j;
	int		len_to_cpy;

	enum {CMD, NOT_CMD} type = CMD;
	tab = my_malloc(sizeof(char*) * (nb_word(str) + 1), garb);
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
			tab[j] = cpy_word(str + i, len_to_cpy, garb);
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

int	init_commande(t_cmd *cmd, char *str, int len, t_list **garb, char **env)
{
	cmd->cmd = get_cmd(str, len, garb);
	cmd->path = find_path(cmd->cmd[0], env);
	//add_node(cmd->path, garb);
	cmd->input_fd = -1;
	cmd->output_fd = -1;
	// fill_redir(str, cmd);
	return (0);
}
