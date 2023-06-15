#include "minishell.h"
#include "libft.h"

int	pwd_is_update(t_context *context)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	add_node(cwd);
	if (ft_streq(cwd, context->pwd))
	{
		free_node(cwd);
		return (1);
	}
	free_node(cwd);
	return (0);
}
