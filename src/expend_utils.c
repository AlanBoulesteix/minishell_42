/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expend_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulest <aboulest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 18:04:11 by aboulest          #+#    #+#             */
/*   Updated: 2023/06/29 18:04:41 by aboulest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_var(char *str)
{
	if (str[0] == '$' && (ft_isalnum(str[1])
			|| str[1] == '_' || str[1] == '\"' || str[1] == '?'))
	{
		if (str[1] == '\"' && (str[2] == ' ' || str[2] == '\0'))
			return (0);
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
	free_node(var);
}

static void	join_str_vec(t_vector *res, char *src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		add_vec(res, src + i);
		i++;
	}
}

static int	add_exit_var(t_vector *res, t_context *context)
{
	char	*tmp;

	tmp = ft_itoa(context->old_exit_value);
	add_node(tmp);
	join_str_vec(res, tmp);
	free_node(tmp);
	return (2);
}

int	add_var(t_vector *res, char *src, t_context *context)
{
	int		i;
	char	*var;
	char	c;

	if (src[1] == '?')
		return (add_exit_var(res, context));
	if (ft_isdigit(src[1]))
	{
		if (src[1] - '0' < context->argc)
			join_str_vec(res, context->argv[src[1] - '0']);
		return (2);
	}
	i = 1;
	while (ft_isalnum(src[i]) || src[i] == '_')
		i++;
	c = src[i];
	src[i] = 0;
	var = get_env_value(&context->env, src + 1);
	src[i] = c;
	if (var)
		join_str_vec(res, var);
	return (i);
}
