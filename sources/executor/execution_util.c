#include "minishell.h"

bool	is_cmd_full_path(t_cmds *cmd)
{
	if (!ft_strchr(cmd->cmd, '/'))
		return (false);
	return (true);
}