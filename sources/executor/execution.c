#include "minishell.h"

int	execute_builtin(t_shell *shell, t_cmds *cmd)
{
	int		ret;

	ret = EXIT_SUCCESS;
	if (!ft_strncmp(cmd->cmd, "cd", -1) && ft_strlen(cmd->cmd) == 2)
		ret = ft_cd(shell, cmd->arg);
	else if (!ft_strncmp(cmd->cmd, "echo", -1) && ft_strlen(cmd->cmd) == 4)
		ret = ft_echo(cmd->arg);
	else if (!ft_strncmp(cmd->cmd, "env", -1) && ft_strlen(cmd->cmd) == 3)
		ret = ft_env(shell->env);
	else if (!ft_strncmp(cmd->cmd, "export", -1) && ft_strlen(cmd->cmd) == 6)
		ret = ft_export(shell, cmd->arg);
	else if (!ft_strncmp(cmd->cmd, "pwd", -1) && ft_strlen(cmd->cmd) == 3)
		ret = ft_pwd(shell);
	else if (!ft_strncmp(cmd->cmd, "unset", -1) && ft_strlen(cmd->cmd) == 5)
		ret = ft_unset(shell, cmd->arg);
	else if (!ft_strncmp(cmd->cmd, "exit", -1) && ft_strlen(cmd->cmd) == 4)
	{
		if (!cmd->prev)
			ret = ft_exit(shell, cmd->arg);
		else
			ret = CMD_NOT_FOUND;
	}
	return (ret);
}

pid_t	execute_cmd(t_shell *shell, t_cmds *cmd, char **envp, char *c)
{
	int		ret;
	pid_t	pid;

	ret = EXIT_SUCCESS;
	pid = fork();
	if (pid == -1)
	{
		errmsg("Fork", NULL, strerror(errno), EXIT_FAILURE);
		exit(errno);
	}
	if (!pid)
	{
		if (cmd->prev && cmd->prev->pipe_fd)
		{
			dup2(cmd->prev->pipe_fd[0], STDIN_FILENO);
			close(cmd->prev->pipe_fd[0]);
			close(cmd->prev->pipe_fd[1]);
		}
		if (cmd->pipe_fd)
		{
			dup2(cmd->pipe_fd[1], STDOUT_FILENO);
			close(cmd->pipe_fd[0]);
			close(cmd->pipe_fd[1]);
		}
		ret = setup_redirect(cmd->io_fd);
		if (ret)
			exit(ret);
		if (is_builtin(c))
			exit(execute_builtin(shell, cmd));
		else
		{
			if (execve(c, cmd->arg, envp) == -1 && !ret)
			{
				if (!cmd->cmd || cmd->cmd[0] == '\0')
				{
					if (cmd->cmd[0] == '\0')
						ret = errmsg("''", NULL, "command not found", EXIT_FAILURE);
					else if (!cmd->io_fd->heredoc && cmd->cmd)
						ret = EXIT_FAILURE;
				}
				else
					ret = error_message(cmd->cmd, true);
			}
			exit(ret);
		}
	}
	else
	{
		if (cmd->prev && cmd->prev->pipe_fd)
		{
			close(cmd->prev->pipe_fd[0]);
			close(cmd->prev->pipe_fd[1]);
		}
	}
	return (pid);
}

int	execute(t_shell *shell)
{
	t_cmds	*cmd;
	char	*path;
	int		ret;
	int		status;
	pid_t	pid;
	pid_t	last_pid;
	// bool	redir;

	// redir = true;
	last_pid = -1;
	cmd = shell->cmds;
	ret = EXIT_SUCCESS;
	while (cmd)
	{
		backup_io(cmd);
		// redir = setup_redirect(cmd->io_fd);
		// if (!redir)
		// {
		// 	redir = true;
		// 	ret = EXIT_FAILURE;
		// 	restore_io(cmd->io_fd);
		// 	cmd = cmd->next;
		// 	continue ;
		// }
		if (is_builtin(cmd->cmd) && !cmd->next && !cmd->prev)
		{
			
			ret = setup_redirect(cmd->io_fd);
			if (!ret)
				ret = execute_builtin(shell, cmd);
		}
		else
		{
			path = search_cmd(cmd->cmd, shell, &ret);
			if (!ret)
				last_pid = execute_cmd(shell, cmd, get_envp(shell->env), path);
		}
		restore_io(cmd->io_fd);
		cmd = cmd->next;
	}
	if (last_pid != -1)
	{
		pid = wait(&status);
		while (pid > 0)
		{
			if (pid == last_pid)
			{
				//^C exitcoce ค้าง
				if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
					ret = 128 + WTERMSIG(status);
				else if (WIFEXITED(status))
					ret = WEXITSTATUS(status);
			}
			pid = wait(&status);
		}
	}
	return (ret);
}
