/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkhienko42 <pkhienko42@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 00:53:24 by sklaokli          #+#    #+#             */
/*   Updated: 2025/05/08 21:40:24 by pkhienko42       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(t_shell *shell, char **av)
{
	int	err_nb;
	int	cnt;

	cnt = -1;
	err_nb = ft_atoi(av[1]);
	while (av[++cnt]);
	printf("exit\n");
	if (cnt > 2)
	{
		err_nb = errmsg_cmd(av[0], NULL, "too many arguments", EXIT_FAILURE);
		return ;
	}
	shell->exit_code = err_nb % 256;
	exit_shell(shell);
}
