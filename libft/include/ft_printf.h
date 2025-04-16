/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkhienko <pkhienko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 18:32:18 by pkhienko          #+#    #+#             */
/*   Updated: 2024/09/07 03:14:01 by pkhienko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>

int		ft_print_hex(unsigned int nb, const char c);
int		ft_printf(const char *format, ...);
int		ft_print_unsigned(unsigned int n);
int		ft_print_ptr(unsigned long nb);
int		ft_print_str(char *str);
int		ft_print_percent(void);
int		ft_print_char(int c);
int		ft_print_nbr(int nb);

#endif