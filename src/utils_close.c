/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_close.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulest <aboulest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 14:59:04 by aboulest          #+#    #+#             */
/*   Updated: 2023/06/30 14:59:35 by aboulest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_and_remove(int fd, t_vector *fds_open)
{
	int	i;

	close(fd);
	i = 0;
	while (i < fds_open->len)
	{
		if (((int *)fds_open->tab)[i] == fd)
			return (remove_vec(fds_open, i));
		i++;
	}
}

void	close_fds_open(t_vector *fds_open)
{
	while (fds_open->len > 0)
	{
		close(((int *)fds_open->tab)[0]);
		remove_vec(fds_open, 0);
	}
}

void	close_fds_open_except(t_vector *fds_open, int except)
{
	int	i;

	i = 0;
	while (fds_open->len > 1)
	{
		if (((int *)fds_open->tab)[0] == except)
			i = 1;
		close(((int *)fds_open->tab)[i]);
		remove_vec(fds_open, i);
	}
}
