/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkhienko42 <pkhienko42@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 00:53:45 by sklaokli          #+#    #+#             */
/*   Updated: 2025/05/07 23:45:47 by pkhienko42       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_unset(t_shell *shell, char **av)
{
	int	i;

	i = 0;
	while (av[++i])
		del_env(&shell->env, av[i]);
	shell->sort_key = update_list_key(shell->env);
	return (EXIT_SUCCESS);
}
