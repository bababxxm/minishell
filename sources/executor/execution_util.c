#include "minishell.h"

void	heredoc_sig_handler(int sig);

char	**get_envp(t_env *env)
{
	char	**envp;
	t_env	*tmp;
	int		len;

	len = 0;
	tmp = env;
	envp = NULL;
	while (tmp)
	{
		len++;
		tmp = tmp->next;
	}
	envp = safealloc(len + 1, sizeof(char *));
	tmp = env;
	len = 0;
	while (tmp)
	{
		envp[len] = strappend(ft_strdup(tmp->key), ft_strdup("="));
		envp[len] = strappend(envp[len], ft_strdup(tmp->value));
		tmp = tmp->next;
		len++;
	}
	envp[len] = NULL;
	return (envp);
}

void	is_wrong_cmd(char *cmd, int *ret)
{
	int	fd;

	if (!cmd)
		return ;
	fd = open(cmd, O_WRONLY);
	if (ft_strchr(cmd, '/') && fd == -1 && !is_dir(cmd))
	{
		if (access(cmd, R_OK))
			*ret = errmsg(cmd, NULL, "Permission denied", CMD_NOT_EXECUTABLE);
		else if (fd == -1 && !is_dir(cmd))
			*ret = errmsg(cmd, NULL, "No such file or directory", CMD_NOT_FOUND);
		else
			*ret = errmsg(cmd, NULL, "command not found", CMD_NOT_FOUND);
		return ;
	}
	*ret = EXIT_SUCCESS;
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

bool is_builtin(char *cmd)
{
    if (!cmd)
        return (false);    
    if ((!ft_strncmp(cmd, "cd", 2) && ft_strlen(cmd) == 2)
        || (!ft_strncmp(cmd, "echo", 4) && ft_strlen(cmd) == 4)
        || (!ft_strncmp(cmd, "env", 3) && ft_strlen(cmd) == 3)
        || (!ft_strncmp(cmd, "export", 6) && ft_strlen(cmd) == 6)
        || (!ft_strncmp(cmd, "pwd", 3) && ft_strlen(cmd) == 3)
        || (!ft_strncmp(cmd, "unset", 5) && ft_strlen(cmd) == 5)
        || (!ft_strncmp(cmd, "exit", 4) && ft_strlen(cmd) == 4))
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
