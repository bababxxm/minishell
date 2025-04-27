/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkhienko <pkhienko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 16:02:05 by pkhienko          #+#    #+#             */
/*   Updated: 2025/04/19 20:55:13 by pkhienko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *find, size_t n)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!str)
		return (NULL);
	if (!*find)
		return ((char *)str);
	if (n == 0)
		return (NULL);
	while (str[i] && i < n)
	{
		j = 0;
		while ((str[i + j] == find[j]) && str[i + j] && (i + j < n))
		{
			j++;
			if (!find[j])
				return ((char *)str + i);
		}
		i++;
	}
	return (NULL);
}
