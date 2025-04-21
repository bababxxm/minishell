#include "minishell.h"

int	ft_unset(t_env *env, char *key)
{
	if (!key)
		return (EXIT_FAILURE);
	del_env(env, key);
	return (EXIT_SUCCESS);
}