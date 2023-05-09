#include "minishell.h"
#include <unistd.h>

int	ft_pwd(char **args, t_context *context)
{
	(void)args;
	(void)context;
	printf("%s\n", getcwd(NULL, 0));
	return (0);
}
