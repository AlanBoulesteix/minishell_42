#include "minishell.h"
#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

// @TODO RM
#include <string.h>
// @TODO RM
t_command	get_cmd(char *input)
{
	t_command	res;
	char		*copy = input;
	int			len;

	for (len=0; copy[len]; copy[len]==' ' ? len++ : *copy++)
		;
	res.args = malloc(len * sizeof(char *));
	res.cmd = strtok(input, " ");
	for (int i = 0; (res.args[i] = strtok(NULL, " ")); i++)
		;
	return (res);
}

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
		// @TODO rm
		exec(get_cmd(input), &context);
		free(input);
	}
}
