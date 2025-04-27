/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkhienko <pkhienko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 20:37:02 by pkhienko          #+#    #+#             */
/*   Updated: 2025/04/19 20:55:13 by pkhienko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*tmp;
	size_t	nb;

	nb = nmemb * size;
	if ((long)nmemb == 0 || (long)size == 0)
		nb = 1;
	else if ((long)nmemb < 0 || (long)size < 0 || nmemb * size > __INT_MAX__)
		return (NULL);
	tmp = malloc(nb);
	if (!tmp)
		return (NULL);
	ft_bzero(tmp, nb);
	return (tmp);
}
