#include "minishell.h"

static bool	is_valid_input(int i, char *str, bool *equal_and_plus)
{
	if (!str || !ft_isalpha(str[0]))
	{
		error_msg("export", str, "not a valid identifier", EXIT_FAILURE);
		return (false);
	}
	while (str[++i])
	{
		if (!ft_isalnum(str[i]))
		{
			if (str[i] == '+' || str[i] == '=')
			{
				if (str[i + 1] && str[i] == '+' && str[i + 1] == '=')
					set_bool(equal_and_plus, true);
				if (str[i] == '=')
					equal_and_plus[0] = true;
				break ;
			}	
			printf("minishell: export: `%s': not a valid identifier\n", str);
			return (false);
		}
	}
	return (true);
}

static void append_export(t_env **env, t_env *tmp, char *new_key, char *value)
{
	char	*new_value;

	if (tmp)
	{
		if (tmp->value)
			new_value = ft_strjoin(tmp->value, value);
		else
			new_value = ft_strdup(value);
		set_env(env, new_key, new_value);
		free_ptr(new_value);
	}
	else
		set_env(env, new_key, value);
}

static void	handle_export(t_env **env, char *key, char *value, bool equal_and_plus[])
{
	t_env	*tmp;
	char	*new_key;

	new_key = handle_key(key, equal_and_plus);
	if (equal_and_plus[0] && equal_and_plus[1])
	{
		tmp = search_env(*env, new_key);
		append_export(env, tmp, new_key, value);
	}
	else if (equal_and_plus[0])
		set_env(env, new_key, value);
	else
	{
		if (search_env(*env, new_key))
			return ;
		set_env(env, new_key, NULL);
		tmp = search_env(*env, new_key);
		tmp->equal = '\0';
	}
	if (equal_and_plus[1])
		free_ptr(new_key);
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

int	ft_export(t_shell *shell, char **av)
{
	int		i;
	int		ret;
	char	**tmp;
	bool	equal_and_plus[2];

	i = 0;
	ret = EXIT_SUCCESS;
	set_bool(&equal_and_plus, false);
	if (av[1])
		while (av[++i])
		{
			if (is_valid_input(-1, av[i], equal_and_plus))
			{
				tmp = ft_split(av[i], '=');
				handle_export(&shell->env, tmp[0], tmp[1], equal_and_plus);
				free_arg(tmp);
			}
			else
				ret = EXIT_FAILURE;
			set_bool(&equal_and_plus, false);
		}
	else
		print_export(shell);
	return (ret);
}
