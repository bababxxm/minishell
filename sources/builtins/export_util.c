/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklaokli <sklaokli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 00:53:28 by sklaokli          #+#    #+#             */
/*   Updated: 2025/05/07 00:53:43 by sklaokli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_bool(bool *data, bool op)
{
	data[0] = op;
	data[1] = op;
}

char	*handle_key(char *str, bool equal_and_plus[])
{
	if (equal_and_plus[1])
		return (ft_strtrim(str, "+"));
	return (str);
}

static void	sort_key(char **keys)
{
	int		i;
	int		j;
	char	*tmp;

	if (!keys || !*keys)
		return ;
	i = 0;
	while (keys[i])
	{
		j = i + 1;
		while (keys[j])
		{
			if (ft_strncmp(keys[i], keys[j], ft_strlen(keys[i])) > 0)
			{
				tmp = keys[i];
				keys[i] = keys[j];
				keys[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

char	**update_list_key(t_env *env)
{
	char	**list;
	t_env	*tmp;
	int		size;

	size = 0;
	tmp = env;
	while (tmp)
	{
		tmp = tmp->next;
		size++;
	}
	list = safealloc(size + 1, sizeof(char *));
	size = 0;
	tmp = env;
	while (tmp)
	{
		list[size++] = tmp->key;
		tmp = tmp->next;
	}
	list[size] = NULL;
	sort_key(list);
	return (list);
}

void	print_export(t_shell *shell)
{
	t_env	*tmp;
	int		i;

	i = 0;
	while (shell->sort_key[i])
	{
		tmp = search_env(shell->env, shell->sort_key[i]);
		if (tmp->key)
			printf("declare -x %s", tmp->key);
		if (tmp->equal)
		{
			printf("=");
			if (tmp->value)
				printf("\"%s\"", tmp->value);
			else
				printf("\"\"");
		}
		printf("\n");
		i++;
	}
}
