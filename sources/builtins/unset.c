/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklaokli <sklaokli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 00:53:45 by sklaokli          #+#    #+#             */
/*   Updated: 2025/05/07 00:53:46 by sklaokli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_unset(t_shell *shell, char **av)
{
	int	i;

	i = 0;
	while (av[++i])
		del_env(&shell->env, av[i]);
	free_ptr(shell->sort_key);
	shell->sort_key = update_list_key(shell->env);
	return (EXIT_SUCCESS);
}
