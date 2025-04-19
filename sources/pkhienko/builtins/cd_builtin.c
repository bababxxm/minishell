#include "minishell.h"

bool	update_path(t_shell *shell, char *path)
{
	char	*old_pwd;
	char	*cur_pwd;

	old_pwd = shell->pwd;
	cur_pwd = path;
	return (false);
}

bool	change_dir(char *path)
{
	

	return (false);
}

void	cd_builtins(t_shell *shell, char **av)
{
	char	*cur_path[PATH_MAX];
	char	*path;

	if (av[2])
		return ; // Too many argurment.
	else if (!av[1] && !ft_strncmp(av[1], "~", 1))
	{
		if (!change_dir("~"))
			return ;
	}
	else if (av[1] && !ft_strncmp(av[1], "-", 1))
	{
		if (!shell->oldpwd)
		{
			perror("");
			return ;
		}
	}


	update_path(shell);
}