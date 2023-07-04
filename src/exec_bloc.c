/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_bloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulest <aboulest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 16:18:13 by aboulest          #+#    #+#             */
/*   Updated: 2023/07/04 16:22:13 by aboulest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/wait.h>

extern int	g_sigint_received;

static int	is_parenthesis(t_block *input)
{
	int	i;

	i = 0;
	while (i < input->len && input->start[i] == ' ')
		i++;
	if (i == input->len)
		return (0);
	return (input->start[i] == '(');
}

static void	exec_parenthesis(t_block *input, t_context *context)
{
	int		i;
	int		len;
	int		cpid;

	i = 0;
	while (i < input->len && input->start[i] == ' ')
		i++;
	len = input->len - 1;
	while (len > 0 && input->start[len] != ')')
		len--;
	cpid = fork();
	if (cpid < 0)
		error(FORK_FAIL_ERRNO, __LINE__, __FILE__);
	if (!cpid)
	{
		context->in_fork = true;
		exec_input(input->start + i + 1, len - i - 1, context);
		exit(context->exit_value);
	}
	set_basic_wait_signals();
	waitpid(cpid, &len, 0);
	set_basic_signals();
	child_pipe_exit_status(len, context);
}

static void	exec_no_op(t_block *input, t_context *context)
{
	if (is_parenthesis(input))
		exec_parenthesis(input, context);
	else
		exec_cmd(input, context);
}

void	exec_block(t_block *input, t_context *context)
{
	if (g_sigint_received)
		return ;
	if (input->op == NO_OP)
		return (exec_no_op(input, context));
	if (input->op == PP)
	{
		exec_pipe(input, context);
		return ;
	}
	if (input->op == OR)
	{
		exec_block(input->left, context);
		if (context->exit_value)
			exec_block(input->right, context);
		return ;
	}
	if (input->op == AND)
	{
		exec_block(input->left, context);
		if (!context->exit_value)
			exec_block(input->right, context);
		return ;
	}
	error_str("exec_block: undefined operator", __LINE__, __FILE__);
}
