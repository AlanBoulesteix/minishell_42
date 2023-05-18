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

char	*cpy_word(char *str, t_list **garb)
{
	int		i;
	char	*dup;
	bool	in_simple;
	bool	in_double;

	i = 0;
	while (str[i] && str[i] != ' ')
	{
		if (str[i] == '\'')
			i++;
		
	}
	dup[i] = '\0';
	return (dup);
}

char **get_cmd(char *str, int len, t_list **garb)
{
	char	**tab;
	int		i;
	int		j;

	enum {CMD, NOT_CMD} type = CMD;
	tab = my_malloc(sizeof(char*) * nb_word(str), garb);
	i = 0;
	j = 0;
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
			tab[j] = cpy_word();
			j++;	
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

int	init_commande(t_cmd *cmd, char *str, int len, t_list **garb)
{
	(void)cmd;
	(void)len;
	printf("%d\n", nb_word(str));
	// cmd->cmd = get_cmd(str, len, garb);
	// cmd->path = get_cmd_path(cmd->cmd[0], garb);
	// fill_redir(str, cmd);
	return (0);
}