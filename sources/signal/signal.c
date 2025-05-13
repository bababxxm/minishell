#include "minishell.h"

void	sighandler(int signum)
{
	if (signum == SIGINT && g_children_code == 0)
	{
		write(STDOUT_FILENO, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void heredoc_sig_handler(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	exit(SIGINT);
}
