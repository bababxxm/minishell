#include "minishell.h"

bool	check_heredoc(t_cmds *cmd)
{
	while (cmd)
	{
		if (cmd->io_fd->heredoc)
			return (true);
		cmd = cmd->next;
	}
	return (false);
}

void	get_sig_ret(int *signum, int *ret, int status)
{
	*signum = WTERMSIG(status);
	if (*signum == SIGINT)
		write(STDOUT_FILENO, "\n", 1);
	else if (*signum == SIGQUIT)
		write(STDOUT_FILENO, "Quit (core dumped)\n", 20);
	*ret = 128 + *signum;
	if (WIFEXITED(status))
		*ret = WEXITSTATUS(status);
}
