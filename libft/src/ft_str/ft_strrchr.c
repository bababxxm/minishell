/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkhienko <pkhienko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 13:29:15 by pkhienko          #+#    #+#             */
/*   Updated: 2024/08/30 13:29:15 by pkhienko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*tmp;
	int		size;

	if (!s)
		return (NULL);
	tmp = NULL;
	size = 0;
	while (*(s + size))
	{
		if (*(s + size) == (char)c)
			tmp = (char *) &*(s + size);
		size++;
	}
	if (*(s + size) == (char)c)
		tmp = (char *) &*(s + size);
	return (tmp);
}
