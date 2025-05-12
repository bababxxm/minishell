/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkhienko42 <pkhienko42@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 00:53:24 by sklaokli          #+#    #+#             */
/*   Updated: 2025/05/13 02:20:04 by pkhienko42       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static long long	ft_atol(const char *str)
{
	unsigned long long	res;
	int					sign;
	int					i;

	if (!str)
		return (0);
	res = 0;
	sign = 1;
	i = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '+' || str[i] == '-')
		if (str[i++] == '-')
			sign = -sign;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + (str[i++] - '0');
		if ((sign == -1 && res > (unsigned long long)LONG_MAX + 1) ||
			(sign == 1 && res > (unsigned long long)LONG_MAX))
			return (257);
	}
	while (ft_isspace(str[i]))
		i++;
	if (str[i] != '\0')
		return (257);
	return (((long long)(res * sign)) % 256);
}

bool	is_number(char *str)
{
	int	i;

	if (!str)
		return (true);
	i = 0;

	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (!ft_isdigit(str[i]))
		return (false);
	while (str[i])
		if (!ft_isdigit(str[i++]))
			break ;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] != '\0')
		return (false);
	return (true);
}

int	ft_exit(t_shell *shell, char **av)
{
	int	cnt;

	cnt = -1;
	while (av[++cnt]);
	printf("exit\n");
	shell->exit_code = ft_atol(av[1]);
	if (cnt > 1 && (!is_number(av[1]) || av[1][0] =='\0'))
		shell->exit_code = errmsg(av[0], av[1], "numeric argument required", 2);
	else if (shell->exit_code == 257)
		shell->exit_code = errmsg(av[0], av[1], "numeric argument required", 2);
	else if (cnt > 2)
		return (errmsg(av[0], NULL, "too many arguments", EXIT_FAILURE));
	exit_shell(shell);
	return (EXIT_SUCCESS);
}
