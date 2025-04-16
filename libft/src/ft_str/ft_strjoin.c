/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkhienko <pkhienko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 19:17:46 by pkhienko          #+#    #+#             */
/*   Updated: 2024/09/01 19:47:50 by pkhienko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*tmp;
	int		i;

	if (!s1 || !s2)
		return (NULL);
	tmp = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
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
