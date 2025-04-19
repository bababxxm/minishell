#include "minishell.h"

void	env_builtin(t_env *env)
{
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
}
