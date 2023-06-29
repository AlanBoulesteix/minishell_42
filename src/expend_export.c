/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expend_export.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlepille <vlepille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 17:29:55 by vlepille          #+#    #+#             */
/*   Updated: 2023/06/29 17:35:23 by vlepille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_equal_offset(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (i - (i > 0 && str[i - 1] == '+'));
		i++;
	}
	return (0);
}

char	*expend_special_export(char *src, t_context *context)
{
	t_vector	res;
	int			i;
	bool		in_simple;
	bool		in_double;

	i = -1;
	init_vec(&res, sizeof(char));
	in_simple = false;
	in_double = false;
	while (src[++i])
	{
		if (src[i] == '\'' && !in_double)
			in_simple = !in_simple;
		else if (src[i] == '\"' && !in_simple)
			in_double = !in_double;
		else if (is_var(src + i) && !in_simple)
			i += add_var(&res, src + i, context) - 1;
		else
			add_vec(&res, src + i);
	}
	add_vec(&res, "");
	return (res.tab);
}

char	*expend_export(
	char *src, t_vector *tokens, int i, t_context *context)
{
	int	equal_offset;

	equal_offset = get_equal_offset(src);
	if (equal_offset && valid(src, equal_offset))
		return (expend_special_export(src, context));
	return (expend_default(src, tokens, i, context));
}
