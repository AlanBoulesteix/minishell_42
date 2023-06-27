#include "minishell.h"
#include <readline/readline.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

extern int	g_sigint_received;

void	handle_sigint(int sig)
{
	(void)sig;
	g_sigint_received = 1;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	set_basic_signals(void)
{
	if (signal(SIGINT, handle_sigint) == SIG_ERR)
		error(SIGNALS_FAIL_ERRNO, __LINE__, __FILE__);
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		error(SIGNALS_FAIL_ERRNO, __LINE__, __FILE__);
}

void	set_children_signals(void)
{
	if (signal(SIGINT, SIG_DFL) == SIG_ERR)
		error(SIGNALS_FAIL_ERRNO, __LINE__, __FILE__);
	if (signal(SIGQUIT, SIG_DFL) == SIG_ERR)
		error(SIGNALS_FAIL_ERRNO, __LINE__, __FILE__);
}

void	handle_wait_sigint(int sig)
{
	(void)sig;
	g_sigint_received = 1;
}

void	set_basic_wait_signals(void)
{
	if (signal(SIGINT, handle_wait_sigint) == SIG_ERR)
		error(SIGNALS_FAIL_ERRNO, __LINE__, __FILE__);
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		error(SIGNALS_FAIL_ERRNO, __LINE__, __FILE__);
}

void	set_pipe_wait_signals(void)
{
	if (signal(SIGINT, handle_wait_sigint) == SIG_ERR)
		error(SIGNALS_FAIL_ERRNO, __LINE__, __FILE__);
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		error(SIGNALS_FAIL_ERRNO, __LINE__, __FILE__);
}

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
