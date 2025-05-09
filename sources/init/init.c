#include "minishell.h"

void	sighandler(int signum)
{
	if (signum == SIGINT)
	{
		write(STDOUT_FILENO, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	init_shell(t_shell *shell, char **env)
{
	shell->input = NULL;
	shell->token = NULL;
	shell->cmds = NULL;
	shell->exit_code = 0;
	shell->env = dup_env(env);
	shell->pwd = get_value(shell->env, "PWD");
	shell->path = get_value(shell->env, "PATH");
	shell->user = get_value(shell->env, "USER");
	shell->home = get_value(shell->env, "HOME");
	shell->oldpwd = get_value(shell->env, "OLDPWD");
	increment_shlvl(shell->env, "SHLVL");
	shell->sort_key = update_list_key(shell->env);
	signal(SIGINT, sighandler);
	signal(SIGQUIT, SIG_IGN);
}