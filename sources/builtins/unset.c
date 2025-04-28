#include "minishell.h"

int	ft_unset(t_env **env, char **av)
{
	int	i;

	i = 0;
	while (av[++i])
		del_env(env, av[i]);
	return (EXIT_SUCCESS);
}
