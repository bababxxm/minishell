/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklaokli <sklaokli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 21:48:51 by sklaokli          #+#    #+#             */
/*   Updated: 2025/05/14 21:48:58 by sklaokli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_io_fd	*new_io_fd(void)
{
	t_io_fd	*io_fd;

	io_fd = safealloc(1, sizeof(t_io_fd));
	io_fd->in_file = NULL;
	io_fd->out_file = NULL;
	io_fd->heredoc = false;
	io_fd->append = false;
	io_fd->err_redir = false;
	io_fd->fd_in = -1;
	io_fd->fd_out = -1;
	io_fd->stdin_backup = -1;
	io_fd->stdout_backup = -1;
	return (io_fd);
}

t_cmds	*new_cmd_full(char *cmd, char **arg, int *pipe_fd, t_io_fd *io_fd)
{
	t_cmds	*command;

	command = safealloc(1, sizeof(t_cmds));
	command->cmd = cmd;
	command->arg = arg;
	command->pipe_fd = pipe_fd;
	command->io_fd = io_fd;
	command->prev = NULL;
	command->next = NULL;
	return (command);
}

void	redir_in(t_token *file, t_io_fd *io_fd)
{
	int	fd;

	fd = open(file->value, O_WRONLY);
	if (fd == -1)
	{
		io_fd->in_file = ft_strdup(file->value);
		io_fd->err_redir = true;
		return ;
	}
	io_fd->in_file = ft_strdup(file->value);
	close(fd);
}

void	redir_out(t_token *file, t_io_fd *io_fd)
{
	int	fd;

	if (access(file->value, F_OK))
		io_fd->err_redir = false;
	else if (access(file->value, W_OK))
		io_fd->err_redir = true;
	fd = open(file->value, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	io_fd->out_file = ft_strdup(file->value);
	io_fd->append = false;
	close(fd);
}

void	redir_append(t_token *file, t_io_fd *io_fd)
{
	int	fd;

	if (access(file->value, F_OK))
		io_fd->err_redir = false;
	else if (access(file->value, W_OK))
		io_fd->err_redir = true;
	fd = open(file->value, O_CREAT | O_WRONLY | O_APPEND, 0644);
	io_fd->out_file = ft_strdup(file->value);
	io_fd->append = true;
	close(fd);
}
