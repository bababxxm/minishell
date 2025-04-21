#include "minishell.h"

int	ft_env(t_env *env)
{
	if (!env)
		return (EXIT_FAILURE);
	while (env)
	{
		if (env->key)
			printf("%s", env->key);
		if (env->equal)
			printf("%c", env->equal);
		if (env->value)
			printf("%s", env->value);
		printf("\n");
		env = env->next;
	}
	return (EXIT_SUCCESS);
}
