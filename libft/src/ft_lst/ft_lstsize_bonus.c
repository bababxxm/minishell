/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkhienko <pkhienko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 14:19:54 by pkhienko          #+#    #+#             */
/*   Updated: 2024/09/13 00:14:17 by pkhienko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

int	ft_lstsize(t_list *lst)
{
	unsigned int	cnt;

	cnt = 0;
	while (lst != NULL)
	{
		cnt++;
		lst = lst->next;
	}
	return (cnt);
}
