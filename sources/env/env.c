/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklaokli <sklaokli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 22:44:48 by sklaokli          #+#    #+#             */
/*   Updated: 2025/04/19 22:46:25 by sklaokli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
 
t_env	*new_env(char *key, char equal, char *value)
{
 	t_env	*new;
 
 	new = malloc(sizeof(t_env));
 	if (!new)
 		return (NULL);
 	new->key = key;
 	new->equal = equal;
 	new->value = value;
 	new->next = NULL;
 	return (new);
}
 
char	*dup_var(char *str, char c)
{
 	int		i;
 	char	*var;
 	
 	var = malloc(sizeof(char) * (ft_strlen_to_c(str, c) + 1));
 	if (!var)
 		return (NULL);
 	i = 0;
 	while (*str && *str != c)
 		var[i++] = *str++;
 	var[i] = '\0';
 	return (var);
}
 
void	set_env(t_env *env, char *key, char *value)
{
 	t_env	*set;
 
 	set = search_env(env, key);
 	if (!set)
 	{
 		set = new_env(ft_strdup(key), '=' ,ft_strdup(value));
		printf("%s\n", set->value);
 		ft_lstadd_back((void **)&env, set);
 	}
 	else
	{
		free(set->value);
		set->value = ft_strdup(value);
	}
}

static void	del_env_util(t_env *cur)
{
	if (cur->key)
		free(cur->key);
	if (cur->value)
		free(cur->value);
	free(cur);

}

void	del_env(t_env **env, char *key)
{
	t_env	*prev;
	t_env	*cur;

	cur	= *env;
	prev = NULL;
	if (!env || !*env || !key)
		return ;
	while (cur)
	{
		if (!ft_strncmp(cur->key, key, ft_strlen(cur->key)) && (ft_strlen(cur->key) == ft_strlen(key)))
		{
			if (prev && cur->next)
				prev->next = cur->next;
			else if (prev && !cur->next)
				prev->next = NULL;
			else
				*env = (*env)->next;
			del_env_util(cur);
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
 		ft_lstadd_back((void **)&dup, new_env(key, '=', value));
 	}
 	return (dup);
}
 
t_env	*search_env(t_env *env, char *key)
{
 	while (env)
 	{
 		if (!ft_strncmp(key, env->key, ft_strlen(env->key)))
 			return (env);
 		env = env->next;
 	}
 	return (NULL);
}
 
void	clear_env(t_env *env)
{
 	t_env	*tmp;
 
 	while (env)
 	{
 		tmp = env;
 		env = env->next;
 		if (tmp->key)
 			free(tmp->key);
 		if (tmp->value)
 			free(tmp->value);
 		free(tmp);
 	}
}
 
