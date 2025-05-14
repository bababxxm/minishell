/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklaokli <sklaokli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 21:48:01 by sklaokli          #+#    #+#             */
/*   Updated: 2025/05/15 03:32:26 by sklaokli         ###   ########.fr       */
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
