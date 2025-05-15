/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_utility.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkhienko <pkhienko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 19:42:05 by pkhienko          #+#    #+#             */
/*   Updated: 2024/09/07 03:23:54 by pkhienko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_printf.h"

static void	ft_putnbr(int n)
{
	long	nb;

	nb = n;
	if (nb < 0)
	{
		ft_print_char('-');
		nb *= -1;
	}
	if (nb > 9)
	{
		ft_putnbr(nb / 10);
		ft_putnbr(nb % 10);
	}
	else
		ft_print_char(nb + '0');
}

int	ft_print_char(int c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_print_str(char *str)
{
	int	cnt;

	cnt = 0;
	if (str == NULL)
	{
		write(1, "(null)", 6);
		return (6);
	}
	while (str[cnt])
	{
		ft_print_char(str[cnt]);
		cnt++;
	}
	return (cnt);
}

int	ft_print_nbr(int n)
{
	int	cnt;
	int	nb;

	nb = n;
	cnt = 1;
	if (n < 0 && n != -2147483648)
	{
		nb *= -1;
		cnt++;
	}
	while (nb > 9)
	{
		cnt++;
		nb /= 10;
	}
	ft_putnbr(n);
	if (n == -2147483648)
		return (11);
	return (cnt);
}

int	ft_print_percent(void)
{
	write(1, "%", 1);
	return (1);
}
