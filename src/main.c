#include "minishell.h"
#include <readline/readline.h>
#include <readline/history.h>

/*
int	count_token(char *input)
{
	int	i;
	int	nb;

	i = -1;
	nb = 0;
	while(input[++i])
	{
	
			nb++;

	}
}

char	**lexing(char *input)
{
	int	i;

	while (input[++i])
	{
		
	}
}
*/





int	main(void)
{
	t_context	context;
//	char		**input;

	if (init_context(&context))
		return (1);
	while (!context.input || !ft_streq(context.input, "exit"))
	{
		context.input = readline("minishell$ ");
		add_history(context.input);
/*		input = lexer(context.input);

		int i = -1;
		while (input[++i])
			printf("token[%d]: %s\n", i, input[i]);
*/	}
}
