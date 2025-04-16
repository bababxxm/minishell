/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkhienko <pkhienko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 18:36:09 by pkhienko          #+#    #+#             */
/*   Updated: 2024/09/07 19:20:04 by pkhienko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_printf.h"

static int	ft_format(va_list ap, const char c)
{
	int	printlen;

	printlen = 0;
	if (c == 'c')
		printlen += ft_print_char(va_arg(ap, int));
	else if (c == 's')
		printlen += ft_print_str(va_arg(ap, char *));
	else if (c == 'p')
		printlen += ft_print_ptr(va_arg(ap, unsigned long));
	else if (c == 'd' || c == 'i')
		printlen += ft_print_nbr(va_arg(ap, int));
	else if (c == 'u')
		printlen += ft_print_unsigned(va_arg(ap, unsigned int));
	else if (c == 'x' || c == 'X')
		printlen += ft_print_hex(va_arg(ap, unsigned int), c);
	else if (c == '%')
		printlen += ft_print_percent();
	return (printlen);
}

int	ft_printf(const char *str, ...)
{
	int		printlen;
	int		cnt;
	va_list	ap;

	if (!str)
		return (-1);
	cnt = 0;
	printlen = 0;
	va_start(ap, str);
	while (str[cnt])
	{
		if (str[cnt] == '%')
		{
			printlen += ft_format(ap, str[cnt + 1]);
			cnt++;
		}
		else
			printlen += ft_print_char(str[cnt]);
		cnt++;
	}
	va_end(ap);
	return (printlen);
}
