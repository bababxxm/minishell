#include "minishell.h"

int	execute_builtin(t_shell *shell, t_cmds *cmd)
{
	int		ret;
	char	*cmd;

	ret = EXIT_SUCCESS;
	if (!ft_strncmp(cmd->cmd, "cd", 2) && ft_strlen(cmd->cmd) == 2)
		ret = ft_cd(shell, cmd->arg);
	else if (!ft_strncmp(cmd->cmd, "echo", 4) && ft_strlen(cmd->cmd) == 4)
		ret = ft_echo(cmd->arg);
	else if (!ft_strncmp(cmd->cmd, "env", 3) && ft_strlen(cmd->cmd) == 3)
		ret = ft_env(shell->env);
	else if (!ft_strncmp(cmd->cmd, "export", 6) && ft_strlen(cmd->cmd) == 6)
		ret = ft_export(shell, cmd->arg);
	else if (!ft_strncmp(cmd->cmd, "pwd", 3) && ft_strlen(cmd->cmd) == 3)
		ret = ft_pwd(shell);
	else if (!ft_strncmp(cmd->cmd, "unset", 5) && ft_strlen(cmd->cmd) == 5)
		ret = ft_unset(shell, cmd->cmd);
	else if (!ft_strncmp(cmd->cmd, "exit", 4) && ft_strlen(cmd->cmd) == 4)
		ret = ft_exit(shell, cmd->cmd);
	else
		ret = CMD_NOT_FOUND;
	return (ret);
}

int	execute_cmd(t_cmds *cmd)
{
	
}

int	execute_cmd_full_path(t_cmds *cmd)
{

}

int	execute(t_shell *shell)
{
	
}