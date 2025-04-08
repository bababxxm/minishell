/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklaokli <sklaokli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 19:47:23 by sklaokli          #+#    #+#             */
/*   Updated: 2025/04/09 02:16:38 by sklaokli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_strlen(char *str)
{
	int	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

int	ft_strlen_to_c(char *str, char c)
{
	int	len;

	len = 0;
	while (str[len] && str[len] != c)
		len++;
	return (len);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n < 1)
		return (0);
	while ((s1[i] == s2[i]) && (s1[i] != '\0') && (i < n - 1))
		i++;
	if ((unsigned char)s1[i] == (unsigned char)s2[i])
		return (0);
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

char	*ft_strdup(char *src)
{
	int		i;
	char	*dst;

	i = -1;
	dst = malloc(ft_strlen(src) + 1);
	if (!dst)
		return (NULL);
	while (src[++i])
		dst[i] = src[i];
	dst[i] = '\0';
	return (dst);
}

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

t_env	*last_env(t_env *env)
{
	while (env && env->next)
		env = env->next;
	return (env);
}

void	env_addback(t_env **env, t_env *new)
{
	if (!*env && new)
		*env = new;
	else if (*env && new)
		last_env(*env)->next = new;
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

t_env	*dup_env(char *env[])
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
		env_addback(&dup, new_env(key, '=', value));
	}
	return (dup);
}

char	*search_env(char *key, t_env *env)
{
	while (env)
	{
		if (!ft_strncmp(key, env->key, ft_strlen(key)))
			return (env->value);
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

void	print_env(t_env *env)
{
	while (env)
	{
		if (env->key)
			printf("%s", env->key);
		if (env->equal)
			printf("%c", env->equal);
		if (env->value)
			printf("%s", env->value);
		printf("\n");
		env = env->next;
	}
}
