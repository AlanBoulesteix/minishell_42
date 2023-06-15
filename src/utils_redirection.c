
#include "minishell.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

void	close_fd(t_cmd *cmd)
{
	if (cmd->input_fd > 2)
		close(cmd->input_fd);
	if (cmd->output_fd > 2)
		close(cmd->output_fd);
}

int	open_infile(char *file)
{
	if (access(file, F_OK) != 0)
	{
		printf_fd(STDERR_FILENO, "minishell: %s: %s\n", file, strerror(errno));
		return (-1);
	}
	else if (access(file, R_OK) == 0)
		return (open(file, O_RDONLY));
	else
	{
		printf_fd(STDERR_FILENO, "minishell: %s: %s\n", file, strerror(errno));
		return (-1);
	}
}

int	open_outfile(char *file)
{
	int	fd;
	if (access(file, F_OK) != 0)
	{
		fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (fd == -1)
			printf_fd(
				STDERR_FILENO, "minishell: %s: %s\n", file, strerror(errno));
	}
	else if (access(file, W_OK) == 0)
	{
		fd = open(file, O_WRONLY | O_TRUNC);
		if (fd == -1)
			printf_fd(
				STDERR_FILENO, "minishell: %s: %s\n", file, strerror(errno));
	}
	else
	{
		printf_fd(STDERR_FILENO, "minishell: %s: %s\n", file, strerror(errno));
		fd = -1;
	}
	return (fd);
}

int	open_outfile_extend(char *file)
{
	int	fd;

	if (access(file, F_OK) != 0)
	{
		fd = open(file, O_CREAT | O_WRONLY | O_APPEND, 0644);
		if (fd == -1)
			printf_fd(
				STDERR_FILENO, "minishell: %s: %s\n", file, strerror(errno));
	}
	else if (access(file, W_OK) == 0)
	{
		fd = open(file, O_WRONLY | O_APPEND);
		if (fd == -1)
			printf_fd(
				STDERR_FILENO, "minishell: %s: %s\n", file, strerror(errno));
	}
	else
	{
		printf_fd(STDERR_FILENO, "minishell: %s: %s\n", file, strerror(errno));
		fd = -1;
	}
	return (fd);
}