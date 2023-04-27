#ifndef MINISHELL_H
# define MINISHELL_H

typedef struct s_context
{
	char	*input;
}	t_context;

int	init_context(t_context *context);

int	ft_streq(char *str1, char *str2);

#endif