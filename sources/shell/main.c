/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklaokli <sklaokli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 21:48:01 by sklaokli          #+#    #+#             */
/*   Updated: 2025/04/19 22:03:17 by sklaokli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char *argv[], char **env)
{
	t_shell	shell;

	init_shell(&shell, env);
	while (true)
	{
		shell.input = readline(PROMPT);
		if (!shell.input)
			exit_shell(&shell);
		execute_cmds(&shell, shell.input);
		add_history(shell.input);
		free(shell.input);
	}
}

void    init_shell(t_shell *shell, char **env)
{    
    shell->cmds = NULL;
    shell->tokens = NULL;
    shell->env = dup_env(env);
    shell->path = search_env("PATH", shell->env);
    shell->user = search_env("USER", shell->env);
    shell->home = search_env("HOME", shell->env);
    shell->oldpwd = search_env("OLDPWD", shell->env);
    shell->pwd = search_env("PWD", shell->env);
}

char    *parser(t_shell *shell, char *input)
{
    return (NULL);
}

void    execute_cmds(t_shell *shell, char *input)
{
	return ;
}

void    exit_shell(t_shell *shell)
{
    printf("exit\n");
    rl_clear_history();
    exit(EXIT_SUCCESS);
}