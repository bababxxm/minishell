/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklaokli <sklaokli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 21:56:43 by sklaokli          #+#    #+#             */
/*   Updated: 2025/04/19 22:04:31 by sklaokli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env_builtin(t_shell *shell)
{
	t_env	*env;

	env = shell->env;
	while (env)
	{
		if (env->key)
			ft_putstr_fd(env->key, STDOUT_FILENO);
		if (env->equal)
			ft_putstr_fd(&env->equal, STDOUT_FILENO);
		if (env->value)
			ft_putstr_fd(env->value, STDOUT_FILENO);
		ft_putendl_fd("", STDOUT_FILENO);
		env = env->next;
	}
}
