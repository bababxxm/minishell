/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkhienko42 <pkhienko42@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 02:04:03 by sklaokli          #+#    #+#             */
/*   Updated: 2025/05/09 09:43:56 by pkhienko42       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_H
# define COMMAND_H

typedef struct s_io_fd
{
	char	*in_file;
	char	*out_file;
	bool	heredoc;
	bool	append;
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

void	backup_io(t_io_fd *io_fd);
void	restore_io(t_io_fd *io_fd);
void	redirect_io(t_io_fd *io_fd);
void	setup_redirect(t_io_fd *io_fd);
bool	is_dir(char *cmd);
bool	is_builtin(char *cmd);
bool	handle_heredoc(t_token *limit, t_io_fd *io_fd);
int		*create_pipe_fd();
int		execute(t_shell *shell);
int		cmd_not_found(t_cmds *cmd, char *c, bool only_not_found);
char	**get_envp(t_env *env);
char	*search_cmd(char *cmd, t_shell *shell);
t_cmds	*built_cmd(t_token	*token);

#endif
