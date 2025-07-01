/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklaokli <sklaokli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 23:39:29 by sklaokli          #+#    #+#             */
/*   Updated: 2025/05/28 23:05:06 by sklaokli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredoc_sig_handler(int sig);

static void	print_err_heredoc(char *line, char *limit)
{
	if (!line)
	{
		ft_putstr_fd("minishell: warning: here-document at line 7 delimited ",
			2);
		ft_putstr_fd("by end-of-file (wanted `", 2);
		ft_putstr_fd(limit, 2);
		ft_putendl_fd("')", 2);
	}
}

static void	parrent_process(t_shell *shell, t_io_fd *io_fd, int pipe_fd[2], pid_t pid)
{
	int	status;

	// close(pipe_fd[0]);
	// (void)io_fd;
	io_fd->fd_in = pipe_fd[0];
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

static void	child_process(t_token *limit, t_io_fd *io_fd, int pipe_fd[2])
{
	char	*line;

	line = NULL;
	while (true)
	{
		line = readline("> ");
		if (!line || (!ft_strncmp(line, limit->raw, -1)
				&& ft_strlen(limit->raw)))
		{
			print_err_heredoc(line, limit->raw);
			break ;
		}
		ft_putendl_fd(line, pipe_fd[1]);
	}
	close(pipe_fd[1]);
	close(pipe_fd[0]);
	(void)io_fd;
	// io_fd->fd_in = pipe_fd[0];
	exit(EXIT_SUCCESS);
}

bool	handle_heredoc(t_shell *shell, t_token *limit, t_io_fd *io_fd)
{
	int		pipe_fd[2];
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
		child_process(limit, io_fd, pipe_fd);
	}
	else
		parrent_process(shell, io_fd, pipe_fd, pid);
	return (true);
}
