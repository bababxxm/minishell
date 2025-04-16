#include "../../include/minishell.h"

void	env_builtin(t_shell *shell)
{
	t_env	*env;

	env = shell->env;
	while (env)
	{
		if (env->key)
			ft_putstr_fd(env->key, STDOUT_FILENO);
		if (env->equal)
			ft_putstr_fd(env->equal, STDOUT_FILENO);
		if (env->value)
			ft_putstr_fd(env->value, STDOUT_FILENO);
		ft_putendl_fd("", STDOUT_FILENO);
		env = env->next;
	}
}
