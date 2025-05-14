/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_util2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklaokli <sklaokli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 21:46:35 by sklaokli          #+#    #+#             */
/*   Updated: 2025/05/15 01:20:22 by sklaokli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	check_heredoc(t_cmds *cmd)
{
	while (cmd)
	{
		if (cmd->io_fd->heredoc)
			return (true);
		cmd = cmd->next;
	}
	return (false);
}

void	get_sig_ret(t_shell *shell, pid_t last_pid, int *ret)
{
	int	signum;
	int	status;

	if (last_pid != -1)
	{
		shell->pid = wait(&status);
		while (shell->pid > 0)
		{
			if (shell->pid == last_pid)
			{
				signum = WTERMSIG(status);
				if (signum == SIGINT)
					write(STDOUT_FILENO, "\n", 1);
				else if (signum == SIGQUIT)
					write(STDOUT_FILENO, "Quit (core dumped)\n", 20);
				*ret = 128 + signum;
				if (WIFEXITED(status))
					*ret = WEXITSTATUS(status);
			}
			shell->pid = wait(&status);
		}
	}
}
