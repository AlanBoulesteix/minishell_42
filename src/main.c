#include "minishell.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

int	main(int argc, char **argv, char **envp)
{
	t_context	context;

	(void)argc;
	(void)argv;
	if (init_context(&context, envp))
		return (1);
	while (!context.input || !ft_streq(context.input, "exit"))
	{
		context.input = readline("minishell$ ");
		add_history(context.input);
	}
}
