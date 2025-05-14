/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklaokli <sklaokli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 23:39:29 by sklaokli          #+#    #+#             */
/*   Updated: 2025/05/14 02:35:19 by sklaokli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void heredoc_sig_handler(int sig);

static void	print_err_heredoc(char *limit)
{
	ft_putstr_fd("minishell: warning: here-document at line 7 delimited ", 2);
	ft_putstr_fd("by end-of-file (wanted `", 2);
	ft_putstr_fd(limit, 2);
	ft_putendl_fd("')", 2);
}

bool	handle_heredoc(t_shell *shell, t_token *limit, t_io_fd *io_fd)
{
	int		pipe_fd[2];
	char	*line;
	int		status;
	pid_t	pid;
	
	if (pipe(pipe_fd) == -1)
		exit_error(shell, errmsg("Pipe", NULL, strerror(errno), 1));
	g_childern_code = 1;
	set_sigint(&shell->sigint, SIG_IGN);
	set_sigquit(&shell->sigint, SIG_IGN);
	pid = fork();
	if (pid == -1)
		exit_error(shell, errmsg("Fork", NULL, strerror(errno), 1));
	if (!pid)
	{
		set_sigint(&shell->sigint, &heredoc_sig_handler);
		while (true)
		{
			line = readline("> ");
			if (!line || (!ft_strncmp(line, limit->raw, -1) && ft_strlen(limit->raw)))
			{
				if (!line)
					print_err_heredoc(limit->raw);
				break ;
			}
			write(pipe_fd[1], line, ft_strlen(line));
			write(pipe_fd[1], "\n", 1);
		}
		close(pipe_fd[1]);
		io_fd->fd_in = pipe_fd[0];
		exit(EXIT_SUCCESS);
	}
	else
	{
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		waitpid(pid, &status, 0);
		set_sigint(&shell->sigint, &sighandler);
		set_sigquit(&shell->sigint, SIG_IGN);
		if (WIFSIGNALED(status))
			shell->exit_code = 128 + WTERMSIG(status);
		else if (WIFEXITED(status))
			shell->exit_code = WEXITSTATUS(status); 
		g_childern_code = 0;
	}
	return (true);
}
