/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkhienko42 <pkhienko42@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 18:28:21 by sklaokli          #+#    #+#             */
/*   Updated: 2025/05/07 23:47:27 by pkhienko42       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*dup_var(char *str, char c)
{
	int		i;
	char	*var;

	var = safealloc((ft_strlen_to_c(str, c) + 1), sizeof(char));
	i = 0;
	while (*str && *str != c)
		var[i++] = *str++;
	var[i] = '\0';
	return (var);
}

char	*get_value(t_env *env, char *key)
{
	t_env	*var;

	var = search_env(env, key);
	if (!var)
		return (NULL);
	else
		return (var->value);
}

