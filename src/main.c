#include "minishell.h"
#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

int	main(void)
{
	t_context	context;
	char		*input;

	input = NULL;
	if (init_context(&context))
		return (1);
	while (!context.exit)
	{
		input = readline("minishell$ ");
		add_history(input);
		printf("Dev_Info :\n");
		printf("<%s>\n", input);
		exec((t_command){input, (char *[]){(char *) NULL}}, &context);
		free(input);
	}
}
