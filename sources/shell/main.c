/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkhienko42 <pkhienko42@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 21:48:01 by sklaokli          #+#    #+#             */
/*   Updated: 2025/05/14 21:11:46 by pkhienko42       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_childern_code = 0;

int	main(int argc, char *argv[], char **env)
{
	t_shell	shell;

	(void)argc;
	(void)argv;
	init_shell(&shell, env);
	while (true)
	{
		shell.input = readline(get_prompt(&shell));
		if (!shell.input)
			exit_shell(&shell);
		execute_cmds(&shell);
		add_history(shell.input);
	}
	exit_shell(&shell);
}

char	*get_exitcode(char *oldprompt, int *exitcode)
{
	int		i;
	char	*newprompt;

	i = 0;
	while (oldprompt[i] && oldprompt[i] != ' ')
		i++;
	*exitcode = 130;
	newprompt = strappend(B_YELLOW"["B_RED, ft_itoa(130));
	newprompt = strappend(newprompt, B_YELLOW"]"B_RED);
	newprompt = strappend(newprompt, &oldprompt[i]);
	oldprompt = "";
	return (newprompt);
}

char    *get_prompt(t_shell *shell)
{
    char    		*path;
    static char		*prompt;
	static int		*exitcode;
    
	if (!shell)
		return (get_exitcode(prompt, exitcode));
	exitcode = &shell->exit_code;
    if (shell->exit_code == 0)
        prompt = strappend(B_YELLOW"["B_GREEN, ft_itoa(shell->exit_code));
    else
        prompt = strappend(B_YELLOW"["B_RED, ft_itoa(shell->exit_code));
    prompt = strappend(prompt, B_YELLOW"] "B_RED);
    prompt = strappend(prompt, ft_strdup(shell->user));
    if (!ft_strncmp(shell->home, shell->pwd, ft_strlen(shell->home)))
        path = strappend("~", ft_strdup(shell->pwd + ft_strlen(shell->home)));
    else
        path = ft_strdup(shell->pwd);
    prompt = strappend(prompt, B_YELLOW":"B_GREEN);
    prompt = strappend(prompt, path);
    prompt = strappend(prompt, B_YELLOW"$ "RESET);
    return (prompt);
}

void	execute_cmds(t_shell *shell)
{
	shell->token = tokenizer(shell);
	if (!shell->token)
		return ;
	shell->cmds = built_cmd(shell->token, shell);
	shell->exit_code = execute(shell, shell->cmds, -1);
}

void	exit_shell(t_shell *shell)
{
	ft_putendl_fd("exit", EXIT_FAILURE);
	close_fds(shell->cmds);
	free_safealloc();
	rl_clear_history();
	exit(shell->exit_code);
}