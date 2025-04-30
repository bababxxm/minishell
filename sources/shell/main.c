/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklaokli <sklaokli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 21:48:01 by sklaokli          #+#    #+#             */
/*   Updated: 2025/04/19 22:47:20 by sklaokli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char *argv[], char **env)
{
	t_shell	shell;

	init_shell(&shell, env);
	ft_export(&shell, (char*[]){"export", "l=123", "d21=q", "D21=q", NULL});
	// ft_export(&shell, (char*[]){"export", NULL});
	printf(GREEN"----------------------------------\n"RESET);
	ft_unset(&shell, (char*[]){"unset", "l", "d21", NULL});
	// ft_export(&shell, (char*[]){"export", NULL});
	clear_env(&shell);
	// while (true)
	// {
	// 	shell.input = readline(PROMPT);
	// 	if (!shell.input)
	// 		ft_exit(&shell, &shell.input);
	// 	execute_cmds(&shell, shell.input);
	// 	add_history(shell.input);
	// 	free_ptr(shell.input);
	// }
}

void	init_shell(t_shell *shell, char **env)
{
	shell->exit_code = 0;
	shell->cmds = NULL;
	shell->input = NULL;
	shell->tokens = NULL;
	shell->env = dup_env(env);
	shell->pwd = search_env(shell->env, "PWD")->value;
	shell->path = search_env(shell->env, "PATH")->value;
	shell->user = search_env(shell->env, "USER")->value;
	shell->home = search_env(shell->env, "HOME")->value;
	shell->sort_key = update_list_key(shell->env);
	shell->oldpwd = search_env(shell->env, "OLDPWD")->value;
}

char	*parser(t_shell *shell, char *input)
{
	return (NULL);
}

void	execute_cmds(t_shell *shell, char *input)
{
	return ;
}
