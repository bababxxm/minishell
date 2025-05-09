/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkhienko42 <pkhienko42@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 22:33:24 by sklaokli          #+#    #+#             */
/*   Updated: 2025/05/09 17:08:07 by pkhienko42       ###   ########.fr       */
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

char	*strappend(char *str, char *append)
{
	char	*tmp;

	if (!str || !append)
		return (NULL);
	if (!str)
		return (ft_strdup(append));
	if (!append)
		return (str);
	tmp = ft_strjoin(str, append);
	return (tmp);
}

void	increment_shlvl(t_env *env, char *key)
{
	int		level;
	char	*value;

	level = ft_atoi(get_value(env, key)) + 1;
	value = ft_itoa(level);
	set_env(&env, key, value);
}
