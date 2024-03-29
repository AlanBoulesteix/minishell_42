/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulest <aboulest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 16:59:02 by aboulest          #+#    #+#             */
/*   Updated: 2023/07/04 16:10:39 by aboulest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <errno.h>

static void	print_err(char *str, int line, char *file)
{
	printf_fd(STDERR_FILENO, "%s:%d -> %s\n", file, line, str);
}

int	error(int err, int line, char *file)
{
	if (err == MALLOC_FAIL_ERRNO)
		print_err("Memory allocation failed", line, file);
	else if (err == FORK_FAIL_ERRNO)
		print_err("Fork creation failed", line, file);
	else if (err == EXECVE_FAIL_ERRNO)
		print_err("Command execution failed", line, file);
	else if (err == PIPE_FAIL_ERRNO)
		print_err("Pipe creation failed", line, file);
	else if (err == OPEN_FAIL_ERRNO)
		print_err("File opening failed", line, file);
	else if (err == CLOSE_FAIL_ERRNO)
		print_err("File closing failed", line, file);
	else if (err == DUP2_FAIL_ERRNO)
		print_err("File descriptor duplication failed", line, file);
	else if (err > 0)
		print_err("Error handling not implementated yet", line, file);
	exit(err);
}

void	error_str(char *str, int line, char *file)
{
	print_err(str, line, file);
	exit(GENERIC_ERRNO);
}

int	print_error(int error)
{
	if (error == 2)
		printf_fd(2, "minishell: syntax error near unexpected token `\"\'\n");
	else if (error == 3)
		printf_fd(2, "minishell: syntax error near unexpected token `\'\'\n");
	else if (error == 4)
		printf_fd(2, "minishell: syntax error near unexpected token `(\'\n");
	else if (error == -4)
		printf_fd(2, "minishell: syntax error near unexpected token `)\'\n");
	return (2);
}

int	print_error_token(int error, char *str)
{
	if (error == -1)
		error = 0;
	if (!str[error])
		printf_fd(2,
			"minishell: syntax error near unexpected token `<newline>'\n");
	else if (str[error] == '&' && str[error + 1] == '&')
		printf_fd(2, "minishell: syntax error near unexpected token `&&'\n");
	else if (str[error] == '|' && str[error + 1] == '|')
		printf_fd(2, "minishell: syntax error near unexpected token `||'\n");
	else if (str[error] == '|' && str[error + 1] != '|')
		printf_fd(2, "minishell: syntax error near unexpected token `|'\n");
	else if (str[error] == '>' && str[error + 1] != '>')
		printf_fd(2, "minishell: syntax error near unexpected token `>'\n");
	else if (str[error] == '<' && str[error + 1] != '<')
		printf_fd(2, "minishell: syntax error near unexpected token `<'\n");
	else if (str[error] == '>' && str[error + 1] == '>')
		printf_fd(2, "minishell: syntax error near unexpected token `>>'\n");
	else if (str[error] == '<' && str[error + 1] == '<')
		printf_fd(2, "minishell: syntax error near unexpected token `<<'\n");
	else if (str[error] == '(')
		printf_fd(2, "minishell: syntax error near unexpected token `('\n");
	else if (str[error] == ')')
		printf_fd(2, "minishell: syntax error near unexpected token `)'\n");
	return (2);
}
