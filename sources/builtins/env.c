#include "minishell.h"

int	ft_env(t_env *env)
{
	while (env)
	{
		if (env->equal)
		{
			if (env->key)
				printf("%s=", env->key);
			if (env->value)
				printf("%s", env->value);
			printf("\n");
		}
		env = env->next;
	}
	return (EXIT_SUCCESS);
}
