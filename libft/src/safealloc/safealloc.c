/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safealloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkhienko42 <pkhienko42@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 19:25:33 by pkhienko42        #+#    #+#             */
/*   Updated: 2025/05/07 23:04:11 by pkhienko42       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
* Returns a pointer to a static list that tracks allocated memory pointer.
*
* @return A pointer to the head of the tracker list.
**/
static t_list	**get_tracker_head(void)
{
	static t_list	*tracker_head;

	return (&tracker_head);
}


/**
* Add a pointer to the static memory pointer list
*
* @param ptr A pointer to be added to the static memory pointer list
**/
static void	track_allocated_ptr(void *ptr)
{
	ft_lstadd_back(get_tracker_head(), ft_lstnew(ptr));
}


/**
* Frees all memory that was allocated using `safealloc`.
**/
void	free_safealloc(void)
{
	ft_lstclear(get_tracker_head(), &free);
}

/**
* Allocates memory and tracks the allocated pointer
* which can be free with `free_safealloc`.
*
* If allocation fails, all memory allocated with `safealloc` will be free
* and will exit form the execution with exit status `1`.
*
* @param count Number of elements to allocate.
* @param size Size of each element.
* @return Pointer to the allocated memory block.
**/
void	*safealloc(size_t count, size_t size)
{
	void	*ptr;

	ptr = ft_calloc(count, size);
	if (!ptr)
	{
		free_safealloc();
		ft_putendl_fd("Error: safealloc failed.", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	track_allocated_ptr(ptr);
	return (ptr);
}
