#include "minishell.h"
#include <unistd.h>
#include <stdlib.h>

int	pwd_cmd(char **args, t_context *context)
{
	char	*cwd;

	(void)args;
	(void)context;
	cwd = getcwd(NULL, 0);
	if (!cwd)
		exit(MALLOC_FAIL_ERRNO);
	printf("%s\n", cwd);
	free(cwd);
	return (0);
}
