#ifndef MINISHELL_H
# define MINISHELL_H

typedef struct s_context
{
	char	*input;
}	t_context;

int	init_context(t_context *context);

#endif