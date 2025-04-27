#include "minishell.h"

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

	if (!keys)
		return ;
	i = 0;
	while (keys[i])
	{
		j = i + 1;
		while (keys[j])
		{
			if (ft_strcmp(keys[i], keys[j]) > 0)
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

char	**create_list_key(t_env *env)
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
	list = safe_malloc(sizeof(char *) * (size + 1));
	if (!list)
		return (NULL);
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
