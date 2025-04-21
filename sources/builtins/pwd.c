#include "minishell.h"

int	ft_pwd(t_shell *shell)
{
	if (shell->pwd)
	{
		printf("%s\n", shell->pwd);
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}
