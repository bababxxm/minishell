/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_ptr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkhienko <pkhienko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 02:13:12 by pkhienko          #+#    #+#             */
/*   Updated: 2024/09/07 03:55:52 by pkhienko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_printf.h"

static int	ft_ptrlen(unsigned long nb)
{
	int	cnt;

	cnt = 0;
	while (nb)
	{
		cnt++;
		nb /= 16;
	}
	return (cnt);
}

static void	ft_printptr(unsigned long nb)
{
	if (nb >= 16)
	{
		ft_printptr(nb / 16);
		ft_printptr(nb % 16);
	}
	else
	{
		if (nb <= 9)
			ft_print_char(nb + '0');
		else if (nb >= 10)
			ft_print_char((nb - 10) + 'a');
	}
}

int	ft_print_ptr(unsigned long ptr)
{
	int	cnt;

	cnt = 0;
	if (ptr == 0)
	{
		cnt += write(1, "(nil)", 5);
		return (cnt);
	}
	cnt += write(1, "0x", 2);
	if (ptr == 0)
		cnt += write(1, "0", 1);
	else
	{
		ft_printptr(ptr);
		cnt += ft_ptrlen(ptr);
	}
	return (cnt);
}
