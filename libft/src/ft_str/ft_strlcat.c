/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkhienko <pkhienko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 22:36:28 by pkhienko          #+#    #+#             */
/*   Updated: 2025/04/19 20:55:13 by pkhienko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	src_length;
	size_t	dest_length;

	if (!dest || !src)
		return (0);
	src_length = ft_strlen(src);
	dest_length = ft_strlen(dest);
	i = 0;
	if (size <= dest_length || size == 0)
		return (size + src_length);
	while (src[i] != '\0' && i < size - dest_length - 1)
	{
		dest[i + dest_length] = src[i];
		i++;
	}
	dest[i + dest_length] = '\0';
	return (dest_length + src_length);
}
