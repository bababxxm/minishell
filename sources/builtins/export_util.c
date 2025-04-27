#include "minishell.h"

char	*handle_key(char *str, bool equal_and_plus[])
{
	if (equal_and_plus[1])
		return (ft_strtrim(str, "+"));
	return (str);
}

void	print_export(t_env *env)
{
	while (env)
	{
		if (env->key)
			printf("declare -x %s", env->key);
		if (env->equal)
		{
			printf("=");
			if (env->value)
				printf("\"%s\"", env->value);
			else
				printf("\"\"");

		}
		printf("\n");
		env = env->next;
	}
}
