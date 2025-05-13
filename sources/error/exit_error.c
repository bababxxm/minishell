#include "minishell.h"

void	exit_error(t_shell *shell, int err_nb)
{
	close_fds(shell->cmds);
	free_safealloc();
	rl_clear_history();
	exit(err_nb);
}
