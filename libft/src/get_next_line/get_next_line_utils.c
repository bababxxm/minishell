/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkhienko <pkhienko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 19:26:26 by pkhienko          #+#    #+#             */
/*   Updated: 2025/04/19 20:55:54 by pkhienko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	clear_list_leak(t_list **list)
{
	t_list	*tmp;

	while (*list)
	{
		tmp = *list;
		*list = (*list)->next;
		free(tmp -> buffer);
		free(tmp);
	}
}

void	add_back(t_list **list, char *new)
{
	t_list	*last_node;
	t_list	*new_node;

	new_node = (t_list *)malloc(sizeof(t_list));
	if (!new_node)
		return ;
	new_node -> buffer = new;
	new_node -> next = NULL;
	if (!*list)
	{
		*list = new_node;
		return ;
	}
	last_node = *list;
	while (last_node -> next != NULL)
		last_node = last_node -> next;
	last_node -> next = new_node;
}

int	check_new_line(t_list *list)
{
	int		i;

	if (!list)
		return (0);
	while (list)
	{
		i = 0;
		while (list -> buffer[i] && i < BUFFER_SIZE)
		{
			if (list -> buffer[i] == '\n')
				return (1);
			i++;
		}
		list = list -> next;
	}
	return (0);
}

int	list_len(t_list *list)
{
	int		cnt;
	int		i;

	if (!list)
		return (0);
	cnt = 0;
	while (list)
	{
		i = 0;
		while (list -> buffer[i])
		{
			if (list -> buffer[i] == '\n')
			{
				cnt++;
				return (cnt);
			}
			i++;
			cnt++;
		}
		list = list -> next;
	}
	return (cnt);
}

void	list_strcpy(t_list *list, char *str)
{
	int	i;
	int	j;

	if (!list)
		return ;
	i = 0;
	while (list)
	{
		j = 0;
		while (list -> buffer[j])
		{
			if (list -> buffer[j] == '\n')
			{
				str[i++] = '\n';
				str[i] = '\0';
				return ;
			}
			str[i++] = list -> buffer[j++];
		}
		list = list -> next;
	}
	str[i] = '\0';
}
