#include "minishell.h"

void	sighandler(int sig)
{
	if (sig == SIGINT && !g_childern_code)
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
	write(STDOUT_FILENO, "\n", 1);
}

void	sigchild(int sig)
{
	(void)sig;
	if (g_childern_code && sig == SIGINT)
		write(STDOUT_FILENO, "\n", 1);
}