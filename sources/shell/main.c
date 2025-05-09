/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkhienko42 <pkhienko42@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 21:48:01 by sklaokli          #+#    #+#             */
/*   Updated: 2025/05/09 17:06:29 by pkhienko42       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char *argv[], char **env)
{
	t_shell	shell;
	char	*prompt;

	(void)argc;
	(void)argv;
	init_shell(&shell, env);
	while (true)
	{
		prompt = strappend(ft_strdup(PROMPT), ft_strdup("["B_YELLOW));
		prompt = strappend(prompt, ft_itoa(shell.exit_code));
		prompt = strappend(prompt, ft_strdup(B_RED"] : ["B_GREEN));
		prompt = strappend(prompt, ft_strdup(shell.pwd));
		prompt = strappend(prompt, ft_strdup(B_RED"]"B_CYAN" $ "RESET));
		shell.input = readline(prompt);
		if (!shell.input)
			exit_shell(&shell);
		execute_cmds(&shell);
		add_history(shell.input);
		// t_cmds	*tmp = shell.cmds;
		// while (tmp)
		// {
		// 	int i = -1;
		// 	printf("cmd= %s\n", tmp->cmd);
		// 	while (tmp->arg[++i])
		// 		printf("arg= %s\n", tmp->arg[i]);
		// 	if (!tmp->pipe_fd)
		// 		printf("NULL\n");
		// 	else
		// 		printf("pipe= %d:%d\n", tmp->pipe_fd[0], tmp->pipe_fd[1]);
		// 	if (tmp->io_fd->in_file)
		// 		printf("In file= %s\n", tmp->io_fd->in_file);
		// 	if (tmp->io_fd->out_file)
		// 		printf("Out file= %s\n", tmp->io_fd->out_file);
		// 	if (tmp->io_fd->heredoc)
		// 		printf("Heredoc= %s\n", tmp->io_fd->heredoc);
		// 	tmp = tmp->next;
		// }
	}
	exit_shell(&shell);
}

void	execute_cmds(t_shell *shell)
{
	shell->token = tokenizer(shell);
	if (!shell->token)
		return ;
	// printf("%s\n", shell->cmds->cmd);
	shell->cmds = built_cmd(shell->token);
	shell->exit_code = execute(shell);
}

void	exit_shell(t_shell *shell)
{
	free_safealloc();
	rl_clear_history();
	exit(shell->exit_code);
}
