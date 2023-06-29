#include "minishell.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

void	close_fd(t_cmd *cmd)
{
	if (cmd->input_fd > 2)
		close(cmd->input_fd);
	if (cmd->output_fd > 2)
		close(cmd->output_fd);
}

int	error_is_directory(char *file, t_context *context)
{
	printf_fd(STDERR_FILENO, "minishell: %s: Is a directory\n", file);
	context->exit_value = 1;
	return (-1);
}

void	print_error_redir(char *file, int fd, t_context *context)
{
	if (fd == -1)
	{
		printf_fd(STDERR_FILENO, "minishell: %s: %s\n", file, strerror(errno));
		context->exit_value = 1;
	}
}

int	open_infile(char *file, t_context *context)
{
	struct stat	buf;

	if (stat(file, &buf) == 0 && S_ISDIR(buf.st_mode))
		return (error_is_directory(file, context));
	if (access(file, F_OK) != 0)
	{
		printf_fd(STDERR_FILENO, "minishell: %s: %s\n", file, strerror(errno));
		context->exit_value = 1;
		return (-1);
	}
	if (access(file, R_OK) == 0)
		return (open(file, O_RDONLY));
	printf_fd(STDERR_FILENO, "minishell: %s: %s\n", file, strerror(errno));
	context->exit_value = 1;
	return (-1);
}

int	open_outfile(char *file, t_context *context)
{
	int			fd;
	struct stat	buf;

	if (stat(file, &buf) == 0 && S_ISDIR(buf.st_mode))
		return (error_is_directory(file, context));
	if (access(file, F_OK) != 0)
	{
		fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		print_error_redir(file, fd, context);
	}
	else if (access(file, W_OK) == 0)
	{
		fd = open(file, O_WRONLY | O_TRUNC);
		print_error_redir(file, fd, context);
	}
	else
	{
		fd = -1;
		print_error_redir(file, fd, context);
	}
	return (fd);
}

int	open_outfile_extend(char *file, t_context *context)
{
	int			fd;
	struct stat	buf;

	if (stat(file, &buf) == 0 && S_ISDIR(buf.st_mode))
		return (error_is_directory(file, context));
	if (access(file, F_OK) != 0)
	{
		fd = open(file, O_CREAT | O_WRONLY | O_APPEND, 0644);
		print_error_redir(file, fd, context);
	}
	else if (access(file, W_OK) == 0)
	{
		fd = open(file, O_WRONLY | O_APPEND);
		print_error_redir(file, fd, context);
	}
	else
	{
		fd = -1;
		print_error_redir(file, fd, context);
	}
	if (fd == -1)
		context->exit_value = 1;
	return (fd);
}
