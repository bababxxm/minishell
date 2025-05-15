/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklaokli <sklaokli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 00:53:20 by sklaokli          #+#    #+#             */
/*   Updated: 2025/05/07 00:53:22 by sklaokli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
