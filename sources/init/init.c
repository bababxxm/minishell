#include "minishell.h"

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
	shell->pid = -1;
	increment_shlvl(shell->env, "SHLVL");
	shell->sort_key = update_list_key(shell->env);
	ft_memset(&shell->sigint, 0, sizeof(shell->sigint));
	set_sigint(&shell->sigint, &sighandler);
	ft_memset(&shell->sigquit, 0, sizeof(shell->sigquit));
	set_sigquit(&shell->sigquit, SIG_IGN);
}