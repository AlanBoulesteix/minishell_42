/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cmd.utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulest <aboulest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 17:55:40 by aboulest          #+#    #+#             */
/*   Updated: 2023/06/29 17:59:47 by aboulest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	nb_arg(t_token *token, int len)
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	while (++i < len)
	{
		if (token[i].type == CMD)
			count++;
	}
	return (count);
}

char	**get_cmd(t_token *token, int len)
{
	char	**cmd;
	int		i;
	int		j;

	cmd = my_malloc(sizeof(char *) * (nb_arg(token, len) + 1));
	i = -1;
	j = 0;
	while (++i < len)
	{
		if (token[i].type == CMD)
		{
			cmd[j] = token[i].f_str;
			j++;
		}
	}
	cmd[j] = NULL;
	return (cmd);
}

t_vector	get_tokens(t_block *input)
{
	t_vector	tokens;
	int			nb_token;

	nb_token = count_token(input->start);
	init_vec(&tokens, sizeof(t_token));
	tokens.tab = tokenization(input->start, nb_token, input->heredoc);
	tokens.len = nb_token;
	tokens.msize = nb_token;
	return (tokens);
}

bool	cmd_is_export(t_vector *vec)
{
	int		i;
	t_token	*token;

	i = -1;
	token = (t_token *)vec->tab;
	while (++i < vec->len)
	{
		if (token[i].type == CMD)
			return (ft_streq(token[i].src, "export"));
	}
	return (false);
}

void	remove_dead_token(t_vector *vec)
{
	int	i;

	i = 0;
	while (i < vec->len)
	{
		if (((t_token *)vec->tab)[i].state == DEAD)
		{
			free_node(((t_token *)vec->tab)[i].f_str);
			free_node(((t_token *)vec->tab)[i].src);
			remove_vec(vec, i);
		}
		else
			i++;
	}
}
