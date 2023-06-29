/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulest <aboulest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 15:49:53 by aboulest          #+#    #+#             */
/*   Updated: 2023/06/29 16:04:51 by aboulest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>
#include <readline/readline.h>

static int	len_var(char *s, int *i, t_context *context)
{
	char	*var;
	char	c;
	int		len;
	int		j;

	j = *i;
	len = 0;
	while (ft_isalnum(s[j]) || s[j] == '_')
		j++;
	c = s[j];
	s[j] = 0;
	var = get_env_value(&context->env, &s[*i]);
	s[j] = c;
	if (var)
		len = ft_strlen(var);
	*i = j;
	free_node(var);
	return (len);
}

static int	len_var_heredoc(char *s, t_context *context)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		if (is_var(&s[i]))
		{
			i++;
			if (s[i] == '?')
				count += nbrlen(context->exit_value);
			else
				count += len_var(s, &i, context);
		}
		else
		{
			i++;
			count ++;
		}
	}
	return (count);
}

static void	duplicate_var(char *dup, char *s2, int *j, t_context *context)
{
	int	i;

	i = 0;
	while (s2 && s2[i])
	{
		if (is_var(&s2[i]))
		{
			i++;
			if (s2[i] == '?' && i++)
				cpy_nbr(dup, context->exit_value, j);
			else
			{
				cpy_var(dup, s2 + i, &context->env, j);
				while (ft_isalnum(s2[i]) || s2[i] == '_')
					i++;
			}
		}
		else
		{
			dup[*j] = s2[i];
			++(*j);
			++i;
		}
	}
}

static char	*join_line(char *s1, char *s2, t_context *context)
{
	int		len;
	int		i;
	int		j;
	char	*dup;

	len = ft_strlen(s1) + len_var_heredoc(s2, context);
	dup = my_malloc(sizeof(char) * (len + 2));
	i = 0;
	j = 0;
	while (s1 && s1[i])
	{
		dup[j] = s1[i];
		++j;
		++i;
	}
	duplicate_var(dup, s2, &j, context);
	dup[j] = '\n';
	dup[j + 1] = '\0';
	return (dup);
}

char	*read_heredoc(char *str, t_context *context)
{
	char		*line;
	char		*all_line;

	line = NULL;
	all_line = NULL;
	while (!ft_streq(line, str))
	{
		free(line);
		line = readline("> ");
		if (!line)
		{
			printf_fd(STDERR_FILENO, "minishell: warning: here-document\
delimited by end-of-file (wanted `%s')\n", str);
			break ;
		}
		if (ft_streq(line, str))
			break ;
		else
		{
			all_line = join_line(all_line, line, context);
			free(line);
			line = NULL;
		}
	}
	return (all_line);
}
