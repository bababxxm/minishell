/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkhienko <pkhienko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 14:36:07 by pkhienko          #+#    #+#             */
/*   Updated: 2025/04/19 21:17:29 by pkhienko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(void **lst, void *new)
{
	t_list	**tmp;
	t_list	*last;

	tmp = (t_list **)lst;
	last = ft_lstlast(*tmp);
	if (!*tmp && new)
		*tmp = new;
	else if (*tmp && new)
		last->next = new;
}
