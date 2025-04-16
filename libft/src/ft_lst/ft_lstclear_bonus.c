/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkhienko <pkhienko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 14:58:09 by pkhienko          #+#    #+#             */
/*   Updated: 2024/08/30 17:32:22 by pkhienko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*node;
	t_list	*tmp;

	if (!lst || !del)
		return ;
	node = *lst;
	while (node != NULL)
	{
		tmp = node;
		node = node -> next;
		ft_lstdelone(tmp, del);
	}
	*lst = NULL;
}
