#include "minishell.h"

static void	update_path(t_shell *shell)
{
	char	cur_path[PATH_MAX];
	
	if (!getcwd(cur_path, PATH_MAX))
		// print error
		return ;
	if (!shell->oldpwd)
		shell->oldpwd = cur_path;
	else
		shell->oldpwd = shell->pwd;
	shell->pwd = cur_path;
	set_env(&shell->env, "PWD", shell->pwd);
	set_env(&shell->env, "OLDPWD", shell->oldpwd);
}

static bool	change_dir(t_shell *shell, char *path)
{
	if (chdir(path) != 0)
		// print perror
		return (false);
	update_path(shell);
	return (true);
}

int	ft_cd(t_shell *shell, char **av)
{
	char	*path;
	
	if (av[2])
	{
		//print Too many argurment.
		return (EXIT_FAILURE);
	}
	else if (!av[1] || !ft_strncmp(av[1], "~", 1) || !ft_strncmp(av[1], "--", 2))
	{
		return (!change_dir(shell, shell->home));
	}
	else if (av[1] && !ft_strncmp(av[1], "-", 1))
	{
		ft_putendl_fd(shell->oldpwd, STDOUT_FILENO);
		return (!change_dir(shell, shell->oldpwd));
	}
	path = av[1];
	return (!change_dir(shell, path));
}
