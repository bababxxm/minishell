#include "minishell.h"

int	pwd_builtin(t_shell *shell)
{
	if (shell->pwd)
	{
		printf("%s\n", shell->pwd);
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}
