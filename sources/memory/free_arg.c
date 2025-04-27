#include "minishell.h"

void	free_arg(char **data)
{
	int	i;

	if (!data || !*data)
		return ;
	i = 0;
	while (data[i])
		free(data[i++]);
	free(data);
}