#include "minishell.h"

int	execute_builtin(t_shell *shell, t_cmds *cmd)
{
	int		ret;

	ret = EXIT_SUCCESS;
	if (!cmd->pipe_fd)
	{
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
			ret = ft_exit(shell, cmd->arg);
	}
	return (ret);
}

int	execute_cmd(t_shell *shell, t_cmds *cmd, char **envp, char *c)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
		return (errmsg("Fork", NULL, strerror(errno), EXIT_FAILURE));
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
		if (is_builtin(c))
			execute_builtin(shell, cmd);
		else if (execve(c, cmd->arg, envp) == -1 && c)
			return (cmd_not_found(cmd, c, true));
			// return (errmsg(cmd->cmd, NULL, strerror(errno), CMD_NOT_FOUND));
	}
	else
	{
		if (cmd->prev && cmd->prev->pipe_fd)
		{
			close(cmd->prev->pipe_fd[0]);
			close(cmd->prev->pipe_fd[1]);
		}
		waitpid(pid, &status, 0);
	}
	return (WEXITSTATUS(status));
}

int	execute(t_shell *shell)
{
	t_cmds	*cmd;
	int		ret;

	cmd = shell->cmds;
	ret = EXIT_SUCCESS;
	while (cmd)
	{
		backup_io(cmd->io_fd);
		setup_redirect(cmd->io_fd);
		cmd = cmd->next;
	}
	cmd = shell->cmds;
	while (cmd)
	{
		if (is_builtin(cmd->cmd) && !cmd->next)
			ret = execute_builtin(shell, cmd);
		else
		{
			ret = cmd_not_found(cmd, search_cmd(cmd->cmd, shell), false);
			if (!ret)
				ret = execute_cmd(shell, cmd, get_envp(shell->env), search_cmd(cmd->cmd, shell));
		}
		restore_io(cmd->io_fd);
		cmd = cmd->next;
	}
	return (ret);
}
