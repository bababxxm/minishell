#include "minishell.h"

static bool	is_valid_input(char *str, bool *has_equal)
{
	int		i;

	i = -1;
	if (!str || ft_isspace(str[0]))
	{
		printf("bash: export: '%s':not a valid identifier\n", str);
		return (false);
	}
	while (str[++i])
	{
		if (ft_isspace(str[i]) && !*has_equal)
		{
			printf("bash: export: '%s':not a valid identifier\n", str);
			return (false);
		}
		if (str[i] == '=')
			*has_equal = true;
	}
	return (true);
}

static	void	handle_export(t_env *env, char *key, char *value, bool has_equal)
{
	t_env	*tmp;

	tmp = NULL;
	if (has_equal)
		set_env(env, key, value);
	else
	{
		if (search_env(env, key))
			return ;
		set_env(env, key, NULL);
		tmp = search_env(env, key);
		tmp->equal = '\0';
	}
}

static void	print_export(t_env *env)
{
	while (env)
	{
		if (env->key)
			printf("declare -x %s", env->key);
		if (env->equal)
		{
			printf("=");
			if (env->value)
				printf("\"%s\"", env->value);
			else
				printf("\"\"");

		}
		printf("\n");
		env = env->next;
	}
}

int	ft_export(t_env *env, char **av)
{
	int		i;
	char	**tmp;
	bool	has_equal;

	i = 0;
	tmp = NULL;
	has_equal = false;
	if (av[1])
	{
		while (av[++i])
		{
			if (is_valid_input(av[i], &has_equal))
			{
				tmp = ft_split(av[i], '=');
				handle_export(env, tmp[0], tmp[1], has_equal);
				while (*tmp)
					free(*tmp++);
			}
			has_equal = false;
		}
	}
	else
	{
		print_export(env);
	}
	return (EXIT_SUCCESS);
}
