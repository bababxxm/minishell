/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklaokli <sklaokli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 00:53:38 by sklaokli          #+#    #+#             */
/*   Updated: 2025/05/15 04:14:08 by sklaokli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_valid_input(int i, char *str, bool *equal_plus, bool	*op)
{
	if (str[0] == '-' && str[1] != '\0')
	{
		*op = true;
		return (errmsg("export", ft_substr(str, 0, 2), "invalid option", 0));
	}
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (errmsg("export", str, "not a valid identifier", false));
	while (str[++i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
		{
			if (str[i + 1] && str[i] == '+' && str[i + 1] == '=')
			{
				set_bool(equal_plus, true);
				break ;
			}
			if (str[i] == '=')
			{
				equal_plus[0] = true;
				break ;
			}
			return (errmsg("export", str, "not a valid identifier", false));
		}
	}
	return (true);
}

static void	append_var(t_env **env, t_env *tmp, char *new_key, char *value)
{
	char	*new_value;

	if (tmp)
	{
		if (tmp->value)
			new_value = ft_strjoin(tmp->value, value);
		else
			new_value = ft_strdup(value);
		set_env(env, new_key, new_value);
	}
	else
		set_env(env, new_key, value);
}

static void	add_var(t_env **env, char *key, char *value, bool equal_plus[])
{
	t_env	*tmp;
	char	*new_key;

	new_key = handle_key(key, equal_plus);
	if (equal_plus[0] && equal_plus[1])
	{
		tmp = search_env(*env, new_key);
		append_var(env, tmp, new_key, value);
	}
	else if (equal_plus[0])
		set_env(env, new_key, value);
	else
	{
		if (search_env(*env, new_key))
			return ;
		set_env(env, new_key, NULL);
		tmp = search_env(*env, new_key);
		tmp->equal = '\0';
	}
	if (equal_plus[1])
		new_key = NULL;
}

static int	export_var(t_shell *shell, char **av, bool *equal_plus, bool op)
{
	int		i;
	int		ret;
	int		len[2];
	char	*tmp[2];

	i = 0;
	ret = EXIT_SUCCESS;
	while (av[++i])
	{
		if (is_valid_input(-1, av[i], equal_plus, &op))
		{
			len[0] = ft_strlen_to_c(av[i], '=');
			tmp[0] = ft_substr(av[i], 0, len[0]);
			len[1] = ft_strlen_to_c(av[i] + len[0] + 1, '\0');
			tmp[1] = ft_substr(av[i], len[0] + 1, len[1]);
			add_var(&shell->env, tmp[0], tmp[1], equal_plus);
		}
		else
			ret = EXIT_FAILURE;
		set_bool(equal_plus, false);
	}
	shell->sort_key = update_list_key(shell->env);
	if (op)
		return (2);
	return (ret);
}

int	ft_export(t_shell *shell, char **av)
{
	int		ret;
	bool	equal_plus[2];

	ret = EXIT_SUCCESS;
	set_bool(equal_plus, false);
	if (av[1])
		ret = export_var(shell, av, equal_plus, false);
	else
		print_export(shell);
	return (ret);
}
