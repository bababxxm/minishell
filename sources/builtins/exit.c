#include "minishell.h"

int	ft_exit(t_shell *shell, char **av)
{
	int	err_nb;

	err_nb = ft_atoi(av[1]);
	printf("exit\n");
	rl_clear_history();
	clear_env(shell);
	if (av[1])
	{
		if (av[2])
			return (errmsg_cmd(av[0], NULL, "too many arguments", err_nb));
		return (err_nb);
	}
	return (EXIT_SUCCESS);
}
