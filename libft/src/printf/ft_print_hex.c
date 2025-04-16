/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkhienko <pkhienko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 23:35:46 by pkhienko          #+#    #+#             */
/*   Updated: 2024/09/07 17:34:12 by pkhienko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_printf.h"

int	ft_hexlen(unsigned int nb)
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

static void	ft_printhex(unsigned int nb, const char c)
{
	if (nb >= 16)
	{
		ft_printhex(nb / 16, c);
		ft_printhex(nb % 16, c);
	}
	else
	{
		if (nb <= 9)
			ft_print_char(nb + '0');
		else if (nb >= 10)
		{
			if (c == 'x')
				ft_print_char((nb - 10) + 'a');
			else if (c == 'X')
				ft_print_char((nb - 10) + 'A');
		}
	}
}

int	ft_print_hex(unsigned int nb, const char c)
{
	int	cnt;

	cnt = 0;
	if (nb == 0)
		cnt++;
	cnt += ft_hexlen(nb);
	ft_printhex(nb, c);
	return (cnt);
}
