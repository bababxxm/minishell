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

// void	close_pipe_fd(t_cmds *cmd, t_cmds *cur_cmd)
// {
// 	if (!cmd)
// 		return ;
// 	close_pipe_fd(cmd->left);
// 	close_pipe_fd(cmd->right);
// 	if (cmd->pipe_fd && cmd != cur_cmd)
// 	{
// 		close(cmd->pipe_fd[0]);
// 		cmd->pipe_fd[0] = -1;
// 		close(cmd->pipe_fd[1]);
// 		cmd->pipe_fd[1] = -1;
// 	}
// }

// void	close_fd(t_cmds *cmd, bool re_io)
// {
// 	if (!cmd)
// 		return ;
// 	if (cmd->io_fd->fd_in != -1)
// 		close(cmd->io_fd->fd_in);
// 	if (cmd->io_fd->fd_out != -1)
// 		close(cmd->io_fd->fd_out);
// 	if (re_io)
// 		restore_io(cmd->io_fd);
// 	close_pipe_fd();
// }

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
	}
}
