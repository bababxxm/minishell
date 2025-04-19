#include "minishell.h"

bool	is_n_flag(char *str)
{
	int	i;

	i = 0;
	if (str[i] != '-')
		return (false);
	i++;
	while (str[i])
	{
		if (str[i] != 'n')
			return (false);
		i++;
	}
	return (true);
}

void	echo_string(char *str, bool n_flag, bool has_next)
{
	int	i;

	i = -1;
	if (!str && n_flag)
		printf("\n");
	if (str)
		printf("%s", str);
	if (has_next)
		printf(" ");
	else if (!n_flag)
		printf("\n");
}

int	echo_builtin(char **av)
{
	bool	has_next;
	bool	n_flag;
	int		i;

	i = 1;
	n_flag = false;
	has_next = false;
	if (av[i] && is_n_flag(av[i]))
	{
		n_flag = true;
		i++;
	}
	while (av[i])
	{
		if (av[i + 1])
			has_next = true;
		echo_string(av[i], n_flag, has_next);
		has_next = false;
		i++;
	}
	return (EXIT_SUCCESS);
}
