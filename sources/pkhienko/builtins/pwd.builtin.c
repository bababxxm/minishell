#include "minishell.h"

int	pwd_builtin(t_shell *shell)
{
	if (shell->pwd)
	{
		ft_putendl_fd(shell->pwd, STDOUT_FILENO);
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}
