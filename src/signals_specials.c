/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_specials.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlepille <vlepille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 16:33:39 by vlepille          #+#    #+#             */
/*   Updated: 2023/06/29 16:34:01 by vlepille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <signal.h>

extern int	g_sigint_received;

void	handle_heredoc_sigint(int sig)
{
	(void)sig;
	close(g_sigint_received);
	exit(128 + sig);
}

void	set_heredoc_signal(void)
{
	if (signal(SIGINT, handle_heredoc_sigint) == SIG_ERR)
		error(SIGNALS_FAIL_ERRNO, __LINE__, __FILE__);
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		error(SIGNALS_FAIL_ERRNO, __LINE__, __FILE__);
}
