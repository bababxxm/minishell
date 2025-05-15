/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkhienko42 <pkhienko42@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 19:17:46 by pkhienko          #+#    #+#             */
/*   Updated: 2025/05/07 23:34:52 by pkhienko42       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*tmp;
	int		i;

	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	tmp = (char *)safealloc(ft_strlen(s1) + ft_strlen(s2) + 1, sizeof(char));
	if (!tmp)
		return (NULL);
	i = 0;
	while (*s1 || *s2)
	{
		if (*s1)
			(tmp)[i++] = *s1++;
		else
			(tmp)[i++] = *s2++;
	}
	tmp[i] = '\0';
	return (tmp);
}
