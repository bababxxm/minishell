#include "minishell.h"

void	backup_io(t_cmds *cmd)
{
	if (!cmd)
		return ;
	cmd->io_fd->stdin_backup = dup(STDIN_FILENO);
	cmd->io_fd->stdout_backup = dup(STDOUT_FILENO);
}