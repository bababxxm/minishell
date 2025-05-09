/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkhienko42 <pkhienko42@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 18:20:18 by sklaokli          #+#    #+#             */
/*   Updated: 2025/05/09 02:19:10 by pkhienko42       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	has_expand(char *str)
{
	int	i;

	if (!str)
		return (false);
	i = -1;
	while (str[++i])
	{
		if (str[i] == '$')
			return (true);
	}
	return (false);
}

int	var_length(char *str)
{
	int	i;

	if (!str || !str[0])
		return (0);
	if (str[0] == '$')
		return (1);
	else if (str[0] == '?' || str[0] == '_' || ft_isdigit(str[0]))
		return (1);
	else if (!ft_isalpha(str[0]) && str[0] != '_')
		return (0);
	i = 0;
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
		i++;
	return (i);
}

char	*ft_expand(char *str, int *ptr, t_env *env, t_shell *shell)
{
	char	*key;
	char	*expand;
	int		start;
	int		len;

	start = ++(*ptr);
	len = var_length(&str[start]);
	if (len == 0)
		return (ft_strdup("$"));
	key = ft_substr(str, start, len);
	if (!ft_strncmp(key, "?", 2))
		expand = ft_itoa(shell->exit_code);
	else if (!ft_strncmp(key, "_", 2))
		expand = ft_strdup("");
	else
		expand = ft_strdup(get_value(env, key));
	*ptr = start + len;
	return (expand);
}

char	*cut_invalid_expand(char *str)
{
	int		i;
	int		len;
	char	*res;

	len = ft_strlen(str) - 1;
	if (len <= 0)
		return (ft_strdup(""));
	res = safealloc(len + 1, sizeof(char));
	i = -1;
	while (++i < len)
		res[i] = str[i];
	res[i] = '\0';
	return (res);
}

char	*expand_variable(char *str, t_env *env, t_shell *shell)
{
	int		i;
	int		start;
	char	*tmp;
	char	*join;

	i = 0;
	join = NULL;
	while (str[i])
	{
		if (str[i] == '$')
			tmp = ft_expand(str, &i, env, shell);
		else
		{
			start = i;
			while (str[i] && str[i] != '$')
				i++;
			tmp = ft_substr(str, start, i - start);
		}
		join = join_and_free(join, tmp);
	}
	return (join);
}
