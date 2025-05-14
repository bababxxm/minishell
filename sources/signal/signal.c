#include "minishell.h"

void	sighandler(int sig)
{
	if (sig == SIGINT && !g_childern_code)
	{
		write(STDOUT_FILENO, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_set_prompt(get_prompt(NULL));
		rl_redisplay();
	}
}

void	set_sigint(t_sa *sigint, void *handler)
{
	sigint->sa_handler = handler;
	sigint->sa_flags = SA_RESTART;
	sigemptyset(&sigint->sa_mask);
	sigaction(SIGINT, sigint, NULL);
}

void	set_sigquit(t_sa *sigquit, void *handler)
{
	sigquit->sa_handler = handler;
	sigquit->sa_flags = SA_RESTART;
	sigemptyset(&sigquit->sa_mask);
	sigaction(SIGQUIT, sigquit, NULL);
}

void 	heredoc_sig_handler(int sig)
{
	if (g_childern_code && sig == SIGINT)
	{
		write(STDOUT_FILENO, "\n", 1);
		exit(130);
	}
}
