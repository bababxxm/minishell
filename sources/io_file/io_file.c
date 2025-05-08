#include "minishell.h"

int	*create_pipe_fd()
{
	int	*pipe_fd;

	pipe_fd = safealloc(2, sizeof(int));
	if (pipe(pipe_fd) == -1)
		perror("Pipe failed");
	return (pipe_fd);
}

void	backup_io(t_io_fd *io_fd)
{
	if (!io_fd)
		return ;
	if (io_fd->stdin_backup == -1)
		io_fd->stdin_backup = dup(STDIN_FILENO);
	if (io_fd->stdout_backup == -1)
		io_fd->stdout_backup = dup(STDOUT_FILENO);
}

void	restore_io(t_io_fd *io_fd)
{
	if (!io_fd)
		return ;
	if (io_fd->stdin_backup != -1) 
	{
		dup2(io_fd->stdin_backup, STDIN_FILENO);
		close(io_fd->stdin_backup);
		io_fd->stdin_backup = -1;
	}
	if (io_fd->stdout_backup != -1) 
	{
		dup2(io_fd->stdout_backup, STDOUT_FILENO);
		close(io_fd->stdout_backup);
		io_fd->stdout_backup = -1;
	}
	if (io_fd->fd_in != -1)
    {
        close(io_fd->fd_in);
        io_fd->fd_in = -1;
    }
    
    if (io_fd->fd_out != -1)
    {
        close(io_fd->fd_out);
        io_fd->fd_out = -1;
    }
}

void	setup_redirect(t_io_fd *io_fd)
{
	int	flags;

	if (io_fd->in_file)
	{
		io_fd->fd_in = open(io_fd->in_file, O_RDONLY);
		if (io_fd->fd_in < 0)
		{
			perror("Open in file");
			return ;
		}
		dup2(io_fd->fd_in, STDIN_FILENO);
		close(io_fd->fd_in);
	}
	else if (io_fd->fd_in != -1 && io_fd->heredoc)
	{
		dup2(io_fd->fd_in, STDIN_FILENO);
		close(io_fd->fd_in);
	}
	if (io_fd->out_file)
	{
		flags = O_WRONLY | O_CREAT;
		if (io_fd->append)
			flags |= O_APPEND;
		else
			flags |= O_TRUNC;
		io_fd->fd_out = open(io_fd->out_file, flags, 0644);
		if (io_fd->fd_out < 0)
		{
			perror("Open out file");
			return ;
		}
		dup2(io_fd->fd_out, STDOUT_FILENO);
		close(io_fd->fd_out);
	}
}
