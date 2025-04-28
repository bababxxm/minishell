/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklaokli <sklaokli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 22:33:24 by sklaokli          #+#    #+#             */
/*   Updated: 2025/04/19 22:33:32 by sklaokli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strlen_to_c(char *str, char c)
{
	int	len;

	len = 0;
	while (str[len] && str[len] != c)
		len++;
	return (len);
}

char	*safe_strjoin(char *str, char *append)
{
	char	*tmp;

	if (!str || !append)
		return (NULL);
	if (!str)
		return (ft_strdup(append));
	if (!append)
		return (str);
	tmp = ft_strjoin(str, append);
	free(str);
	return (tmp);
}

void	*safe_malloc(size_t	size)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
	{
		perror("Malloc failed");
		return (NULL);
	}
	return (ptr);
}
