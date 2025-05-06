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

	(void)argc;
	(void)argv;
	init_shell(&shell, env);
	while (true)
	{
		shell.input = readline(PROMPT);
		if (!shell.input)
			exit_shell(&shell);
		execute_cmds(&shell, shell.input);
		add_history(shell.input);
		free_ptr(shell.input);
	}
}

void	execute_cmds(t_shell *shell, char *input)
{
	char	*line;

	line = ft_strdup(input);
	shell->token = tokenizer(shell);
	clear_tokens(shell->token);
	free_ptr(line);
}

void	exit_shell(t_shell *shell)
{
	clear_shell(shell);
	exit(shell->exit_code);
}
