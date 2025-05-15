/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkhienko42 <pkhienko42@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 14:36:07 by pkhienko          #+#    #+#             */
/*   Updated: 2025/05/07 23:18:52 by pkhienko42       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	**tmp;
	t_list	*last;

	tmp = lst;
	last = ft_lstlast(*tmp);
	if (!*tmp && new)
		*tmp = new;
	else if (*tmp && new)
		last->next = new;
}
