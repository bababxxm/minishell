/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_util.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklaokli <sklaokli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 21:55:12 by sklaokli          #+#    #+#             */
/*   Updated: 2025/05/14 21:55:13 by sklaokli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	dup_close(int in_out, int fd)
{
	dup2(in_out, fd);
	close(in_out);
}

void	set_flag(t_io_fd *io_fd, int *flags)
{
	*flags = O_WRONLY | O_CREAT;
	if (io_fd->append)
		*flags |= O_APPEND;
	else
		*flags |= O_TRUNC;
}

void	setup_pipe(t_cmds *cmd)
{
	if (cmd->prev && cmd->prev->pipe_fd)
	{
		dup2(cmd->prev->pipe_fd[0], STDIN_FILENO);
		close(cmd->prev->pipe_fd[0]);
		close(cmd->prev->pipe_fd[1]);
	}
	if (cmd->pipe_fd)
	{
		dup2(cmd->pipe_fd[1], STDOUT_FILENO);
		close(cmd->pipe_fd[0]);
		close(cmd->pipe_fd[1]);
	}
}

void	close_pipe(t_cmds *cmd)
{
	if (cmd->prev && cmd->prev->pipe_fd)
	{
		close(cmd->prev->pipe_fd[0]);
		close(cmd->prev->pipe_fd[1]);
	}
}
