/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_util.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklaokli <sklaokli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 21:44:36 by sklaokli          #+#    #+#             */
/*   Updated: 2025/05/15 04:14:27 by sklaokli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredoc_sig_handler(int sig);

char	**get_envp(t_env *env)
{
	char	**envp;
	t_env	*tmp;
	int		len;
	int		i;

	i = 0;
	len = ft_lstsize((t_list *)env);
	envp = safealloc(len + 1, sizeof(char *));
	tmp = env;
	while (tmp)
	{
		envp[i] = strappend(ft_strdup(tmp->key), ft_strdup("="));
		if (!tmp->value)
			envp[i] = strappend(envp[i], ft_strdup(""));
		else
			envp[i] = strappend(envp[i], ft_strdup(tmp->value));
		tmp = tmp->next;
		i++;
	}
	envp[i] = NULL;
	return (envp);
}

static void	is_wrong_cmd(char *cmd, int *ret)
{
	int	fd;

	if (!cmd)
		return ;
	fd = open(cmd, O_WRONLY);
	if (ft_strchr(cmd, '/') && fd == -1 && !is_dir(cmd))
	{
		if (fd == -1 && !is_dir(cmd))
			*ret = errmsg(cmd, NULL,
					"No such file or directory", CMD_NOT_FOUND);
		else if (access(cmd, R_OK))
			*ret = errmsg(cmd, NULL, "Permission denied", CMD_NOT_EXECUTABLE);
		else
			*ret = errmsg(cmd, NULL, "command not found", CMD_NOT_FOUND);
		return ;
	}
	*ret = EXIT_SUCCESS;
	if (fd >= 0)
		close(fd);
}

char	*search_cmd(char *cmd, t_shell *shell, int *ret)
{
	char	**all_path;
	char	*select_path;
	char	*new_cmd;
	int		i;

	if (!cmd)
		return (NULL);
	i = -1;
	all_path = ft_split(get_value(shell->env, "PATH"), ':');
	if (!all_path)
		return (ft_strdup(cmd));
	while (all_path[++i])
	{
		select_path = ft_strjoin(all_path[i], "/");
		new_cmd = ft_strjoin(select_path, cmd);
		if (!access(new_cmd, F_OK | X_OK))
		{
			is_wrong_cmd(cmd, ret);
			return (new_cmd);
		}
	}
	return (ft_strdup(cmd));
}

bool	is_builtin(char *cmd)
{
	if (!cmd)
		return (false);
	if ((!ft_strncmp(cmd, "cd", -1) && ft_strlen(cmd) == 2)
		|| (!ft_strncmp(cmd, "echo", -1) && ft_strlen(cmd) == 4)
		|| (!ft_strncmp(cmd, "env", -1) && ft_strlen(cmd) == 3)
		|| (!ft_strncmp(cmd, "export", -1) && ft_strlen(cmd) == 6)
		|| (!ft_strncmp(cmd, "pwd", -1) && ft_strlen(cmd) == 3)
		|| (!ft_strncmp(cmd, "unset", -1) && ft_strlen(cmd) == 5)
		|| (!ft_strncmp(cmd, "exit", -1) && ft_strlen(cmd) == 4))
		return (true);
	return (false);
}

bool	is_dir(char *cmd)
{
	struct stat	st;

	if (stat(cmd, &st) == -1)
		return (false);
	return (S_ISDIR(st.st_mode));
}
