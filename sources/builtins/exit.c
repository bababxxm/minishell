/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkhienko42 <pkhienko42@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 00:53:24 by sklaokli          #+#    #+#             */
/*   Updated: 2025/05/09 03:45:42 by pkhienko42       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_number(char *str)
{
	int	i;

	if (!str)
		return (true);
	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i++]))
			return (false);
	}
	return (true);
}

int	ft_exit(t_shell *shell, char **av)
{
	int	cnt;

	cnt = -1;
	while (av[++cnt]);
	printf("exit\n");
	if (cnt > 1 && !is_number(av[1]))
	{
		shell->exit_code = errmsg(av[0], av[1], "numeric argument required", 2);
		exit_shell(shell);
	}
	else if (cnt > 2)
		return (errmsg(av[0], NULL, "too many arguments", EXIT_FAILURE));
	shell->exit_code = ft_atoi(av[1]) % 256;
	exit_shell(shell);
	return (EXIT_SUCCESS);
}
