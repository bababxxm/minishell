/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkhienko42 <pkhienko42@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 22:44:48 by sklaokli          #+#    #+#             */
/*   Updated: 2025/05/07 23:49:12 by pkhienko42       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*new_env(char *key, char equal, char *value)
{
	t_env	*new;

	new = safealloc(1,  sizeof(t_env));
	new->key = key;
	new->equal = equal;
	new->value = value;
	new->next = NULL;
	return (new);
}

void	set_env(t_env **env, char *key, char *value)
{
	t_env	*set;

	set = search_env(*env, key);
	if (!set)
	{
		set = new_env(ft_strdup(key), '=', ft_strdup(value));
		ft_lstadd_back((t_list **)env, (t_list *)set);
	}
	else
	{
		set->equal = '=';
		set->value = ft_strdup(value);
	}
}

void	del_env(t_env **env, char *key)
{
	t_env	*prev;
	t_env	*cur;

	cur = *env;
	prev = NULL;
	if (!env || !*env || !key)
		return ;
	while (cur)
	{
		if (!ft_strncmp(cur->key, key, ft_strlen(cur->key))
			&& (ft_strlen(cur->key) == ft_strlen(key)))
		{
			if (prev && cur->next)
				prev->next = cur->next;
			else if (prev && !cur->next)
				prev->next = NULL;
			else
				*env = (*env)->next;
			return ;
		}
		prev = cur;
		cur = cur->next;
	}
}

t_env	*dup_env(char **env)
{
	int		i;
	int		j;
	char	*key;
	char	*value;
	t_env	*dup;

	i = -1;
	j = 0;
	dup = NULL;
	while (env[++i])
	{
		j = 0;
		key = dup_var(&env[i][j], '=');
		while (env[i][j] && env[i][j] != '=')
			j++;
		j++;
		value = dup_var(&env[i][j], '\0');
		ft_lstadd_back((t_list **)&dup, (t_list *)new_env(key, '=', value));
	}
	return (dup);
}

t_env	*search_env(t_env *env, char *key)
{
	while (env)
	{
		if (!ft_strncmp(key, env->key, ft_strlen(env->key))
			&& ft_strlen(key) == ft_strlen(env->key))
			return (env);
		env = env->next;
	}
	return (NULL);
}
