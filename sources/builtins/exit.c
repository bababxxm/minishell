/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkhienko42 <pkhienko42@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 00:53:24 by sklaokli          #+#    #+#             */
/*   Updated: 2025/05/07 23:48:58 by pkhienko42       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exit(t_shell *shell, char **av)
{
	int	err_nb;

	(void)shell;
	err_nb = ft_atoi(av[1]);
	printf("exit\n");
	rl_clear_history();
	if (av[1])
	{
		if (av[2])
			return (errmsg_cmd(av[0], NULL, "too many arguments", err_nb));
		return (err_nb);
	}
	return (EXIT_SUCCESS);
}
