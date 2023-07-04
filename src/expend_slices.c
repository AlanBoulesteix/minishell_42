/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expend_slices.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulest <aboulest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 16:26:39 by aboulest          #+#    #+#             */
/*   Updated: 2023/07/04 16:29:23 by aboulest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_slice_type(char c)
{
	if (c == '\'')
		return (SIMPLE);
	else if (c == '\"')
		return (DOUBLE);
	else
		return (NONE);
}

static int	len_slice(char *src)
{
	const int	type = get_slice_type(*src);
	int			i;

	i = 0;
	src += (type == SIMPLE || type == DOUBLE);
	if (type == NONE)
	{
		while (src[i] && src[i] != '\'' && src[i] != '\"')
			i++;
	}
	else if (type == SIMPLE)
	{
		while (src[i] && src[i] != '\'')
			i++;
	}
	else
	{
		while (src[i] && src[i] != '\"')
			i++;
	}
	return (i);
}

static void	copy_to_slice(t_slice *slice, char *src, int *i)
{
	int	j;

	slice->str = my_malloc((slice->len + 1) * sizeof(char));
	j = 0;
	*i += (slice->quote_type == SIMPLE || slice->quote_type == DOUBLE);
	while (j < slice->len)
	{
		slice->str[j] = src[*i];
		j++;
		(*i)++;
	}
	slice->str[j] = '\0';
}

t_slice	*create_slices(char *src)
{
	t_vector	slices;
	int			i;
	int			j;

	init_vec(&slices, sizeof(t_slice));
	i = 0;
	j = 0;
	while (src[i])
	{
		add_vec(&slices,
			&(t_slice){NULL, len_slice(src + i), get_slice_type(src[i])});
		copy_to_slice(&((t_slice *)slices.tab)[j], src, &i);
		i += (((t_slice *)slices.tab)[j].quote_type == SIMPLE
				|| ((t_slice *)slices.tab)[j].quote_type == DOUBLE);
		j++;
	}
	add_vec(&slices, &(t_slice){NULL, 0, END});
	return (slices.tab);
}

void	expend_slice(t_slice *slice, t_context *context)
{
	t_vector	res;
	int			i;

	if (slice->quote_type == SIMPLE)
		return ;
	init_vec(&res, sizeof(char));
	i = -1;
	while (slice->str[++i])
	{
		if (is_var(slice->str + i))
		{
			i += add_var(&res, slice->str + i, context) - 1;
		}
		else
			add_vec(&res, slice->str + i);
	}
	add_vec(&res, "");
	free_node(slice->str);
	slice->str = res.tab;
}
