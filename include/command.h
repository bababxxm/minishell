/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklaokli <sklaokli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 02:04:03 by sklaokli          #+#    #+#             */
/*   Updated: 2025/04/09 04:05:11 by sklaokli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_H
# define COMMAND_H

typedef struct s_io_fd
{
	char	*heredoc;
	char	*in_file;
	char	*out_file;
	int		fd_in;
	int		fd_out;
	int		stdin_backup;
	int		stdout_backup;
}	t_io_fd;


typedef struct s_cmds
{
	char			*cmd;
	char			**arg;
	int				*pipe_fd;
	t_io_fd			*io_fd;
	struct s_cmds	*prev;
	struct s_cmds	*next;
}	t_cmds;

int		*create_pipe_fd();
t_cmds	*built_cmd(t_shell *shell, t_token	*token);

#endif
