#include "minishell.h"
#include <readline/readline.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

void	handle_sigint(int sig)
{
	(void)sig;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	set_parent_signals(void)
{
	if (signal(SIGINT, handle_sigint) == SIG_ERR)
		error(SIGNALS_FAIL_ERRNO, __LINE__, __FILE__);
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		error(SIGNALS_FAIL_ERRNO, __LINE__, __FILE__);
}

void	set_children_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	set_wait_signals(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void handle_heredoc_sigint(int sig)
{
	(void)sig;
}

void	set_heredoc_signal(void)
{

	if (signal(SIGINT, SIG_DFL) == SIG_ERR)
		error(SIGNALS_FAIL_ERRNO, __LINE__, __FILE__);
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		error(SIGNALS_FAIL_ERRNO, __LINE__, __FILE__);
}