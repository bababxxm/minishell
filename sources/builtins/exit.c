#include "minishell.h"

int	ft_exit(t_shell *shell, char **av)
{
    printf("exit\n");
    rl_clear_history();
	clear_env(shell);
	if (av[1])
	{
		if (av[2])
			error_msg(av[0], NULL, "too many arguments", STDERR_FILENO);
		return (ft_atoi(av[1]));
	}
	return (EXIT_SUCCESS);
}
