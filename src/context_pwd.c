#include "minishell.h"
#include "libft.h"

int	pwd_is_update(t_context *context)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		exit(MALLOC_FAIL_ERRNO);
	if (ft_streq(cwd, context->pwd))
	{
		free(cwd);
		return (1);
	}
	free(cwd);
	return (0);
}
