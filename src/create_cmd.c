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
			while (str[i] && !is_redir(&str[i]) && str[i] != ' ')
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

char	*cpy_word(char *str, int len)
{
	int		i;
	int		j;
	char	*dup;

	i = 0;
	j = 0;
	dup = my_malloc(sizeof(char) * (len + 1));
	while (str[i] && i < len)
	{
  		dup[j] = str[i];
		j++;
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
	tab = my_malloc(sizeof(char *) * (nb_word(str) + 1));
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
			len_to_cpy = 0;
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
	char	*extension;
	char	c;

	(void)len;
	str[len] = 0;
	c = str[len];
	extension = expender(str, env);
	str[len] = c;
	cmd->cmd = get_cmd(extension, ft_strlen(extension));
	open_redirection(extension, cmd);
	if (is_builtin(cmd->cmd[0]))
		cmd->path = NULL;
	else
	{
		cmd->path = find_path(cmd->cmd[0], env);
		if (!cmd->path)
			return (1);
	}
	add_node(cmd->path);
	return (0);
}
