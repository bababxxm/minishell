/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_unsigned.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkhienko <pkhienko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 22:54:31 by pkhienko          #+#    #+#             */
/*   Updated: 2024/09/07 03:17:57 by pkhienko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_printf.h"

static void	ft_printnb(unsigned int n)
{
	if (n > 9)
		ft_print_unsigned(n / 10);
	if (n < 10)
	{
		ft_print_char(n + '0');
		return ;
	}
	ft_print_char((n % 10) + '0');
}

int	ft_print_unsigned(unsigned int n)
{
	int	cnt;

	ft_printnb(n);
	cnt = 1;
	while (n > 9)
	{
		cnt++;
		n /= 10;
	}
	return (cnt);
}
