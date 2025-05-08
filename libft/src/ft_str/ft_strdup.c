/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkhienko42 <pkhienko42@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 15:29:59 by pkhienko          #+#    #+#             */
/*   Updated: 2025/05/07 23:35:01 by pkhienko42       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*dest;
	int		i;

	if (!s)
		return (NULL);
	i = -1;
	dest = (char *) safealloc(ft_strlen(s) + 1, sizeof(char));
	if (!dest)
		return (NULL);
	while (s[++i])
		dest[i] = s[i];
	dest[i] = '\0';
	return (dest);
}
