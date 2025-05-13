#include "minishell.h"

void heredoc_sig_handler(int sig);

bool	handle_heredoc(t_token *limit, t_io_fd *io_fd)
{
	int		pipe_fd[2];
	char	*line;

	if (pipe(pipe_fd) == -1)
		return (errmsg("Pipe", NULL, strerror(errno), 0));
	signal(SIGINT, heredoc_sig_handler);
	while (true)
	{
		line = readline("> ");
		if (!line || (!ft_strncmp(line, limit->raw, -1) && ft_strlen(limit->raw)))
			break ;
		write(pipe_fd[1], line, ft_strlen(line));
		write(pipe_fd[1], "\n", 1);
	}
	signal(SIGINT, sighandler);
	close(pipe_fd[1]);
	io_fd->fd_in = pipe_fd[0];
	return (true);
}