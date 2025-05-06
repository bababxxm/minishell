#include "minishell.h"

int	*create_pipe_fd()
{
	int	*pipe_fd;

	pipe_fd = safe_malloc(sizeof(int) * 2);
	if (!pipe_fd)
		return (NULL);
	if (pipe(pipe_fd) == -1)
		perror("Pipe failed");
	return (pipe_fd);
}

// void	backup_io(t_io_fd *io)
// {
// 	if (!io)
// 		return ;
// 	if (io->stdin_backup == -1)
// 		io->stdin_backup = dup(STDIN_FILENO);
// 	if (io->stdout_backup == -1)
// 		io->stdout_backup = dup(STDOUT_FILENO);
// }

// void	restore_io(t_io_fd *io)
// {
// 	if (!io)
// 		return ;
// 	if (io->stdin_backup != -1) 
// 	{
// 		dup2(io->stdin_backup, STDIN_FILENO);
// 		close(io->stdin_backup);
// 		io->stdin_backup = -1;
// 	}
// 	if (io->stdout_backup != -1) 
// 	{
// 		dup2(io->stdout_backup, STDIN_FILENO);
// 		close(io->stdout_backup);
// 		io->stdout_backup = -1;
// 	}
// }

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
