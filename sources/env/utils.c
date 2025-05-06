/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklaokli <sklaokli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 18:28:21 by sklaokli          #+#    #+#             */
/*   Updated: 2025/05/06 18:30:02 by sklaokli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*dup_var(char *str, char c)
{
	int		i;
	char	*var;

	var = safe_malloc(sizeof(char) * (ft_strlen_to_c(str, c) + 1));
	if (!var)
		return (NULL);
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

void	del_env_util(t_env *cur)
{
	free_ptr(cur->key);
	free_ptr(cur->value);
	free_ptr(cur);
}
