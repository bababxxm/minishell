/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklaokli <sklaokli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 00:53:11 by sklaokli          #+#    #+#             */
/*   Updated: 2025/05/07 00:53:12 by sklaokli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	update_path(t_shell *shell)
{
	char	cur_path[PATH_MAX];

	if (!getcwd(cur_path, PATH_MAX))
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
	{
		errmsg_cmd("cd", path, "No such file or directory", EXIT_FAILURE);
		return (false);
	}
	update_path(shell);
	return (true);
}

int	ft_cd(t_shell *shell, char **av)
{
	char	*path;

	if (av[2])
		return (errmsg_cmd("cd", NULL, "too many argurments", EXIT_FAILURE));
	else if (!av[1] || !ft_strncmp(av[1], "~", 1)
		|| !ft_strncmp(av[1], "--", 2))
		return (!change_dir(shell, shell->home));
	else if (av[1] && !ft_strncmp(av[1], "-", 1))
	{
		ft_putendl_fd(shell->oldpwd, STDOUT_FILENO);
		return (!change_dir(shell, shell->oldpwd));
	}
	path = av[1];
	return (!change_dir(shell, path));
}
