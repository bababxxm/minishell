#include "minishell.h"

void	sighandler(int sig)
{
	write(STDOUT_FILENO, "default", 1);
	// printf("a");
	if (sig == SIGINT && !g_childern_code)
	{
		write(STDOUT_FILENO, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	set_sigint(t_sa *sigint, void *ft)
{
	sigint->sa_handler = ft;
	sigint->sa_flags = SA_RESTART;
	sigemptyset(&sigint->sa_mask);
	sigaction(SIGINT, sigint, NULL);
}

void	set_sigquit(t_sa *sigquit, void *ft)
{
	sigquit->sa_handler = ft;
	sigquit->sa_flags = SA_RESTART;
	sigemptyset(&sigquit->sa_mask);
	sigaction(SIGQUIT, sigquit, NULL);
}

void 	heredoc_sig_handler(int sig)
{
	write(STDOUT_FILENO, "heredoc", 1);
	if (g_childern_code && sig == SIGINT)
	{
		write(STDOUT_FILENO, "\n", 1);
		exit(130);
	}
}

void	sigchild(int sig)
{
	write(STDOUT_FILENO, "child", 1);
	if (g_childern_code && sig == SIGINT)
	{
		write(STDOUT_FILENO, "\n", 1);
		exit(130);
	}
	else if (g_childern_code && sig == SIGQUIT)
	{
		write(STDOUT_FILENO, "^\\Quit (core dumped)\n", 21);
		exit(131);
	}
}