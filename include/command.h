/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklaokli <sklaokli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 02:04:03 by sklaokli          #+#    #+#             */
/*   Updated: 2025/05/15 01:38:41 by sklaokli         ###   ########.fr       */
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
	bool	err_redir;
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

void	close_fds(t_cmds *cmd);
void	backup_io(t_cmds *cmd);
void	close_pipe(t_cmds *cmd);
void	setup_pipe(t_cmds *cmd);
void	restore_io(t_io_fd *io_fd);
void	dup_close(int in_out, int fd);
void	set_flag(t_io_fd *io_fd, int *flags);
void	redir_in(t_token *file, t_io_fd *io_fd);
void	redir_out(t_token *file, t_io_fd *io_fd);
void	redir_append(t_token *file, t_io_fd *io_fd);
void	get_sig_ret(t_shell *shell, pid_t last_pid, int *ret);
void	handle_redirection(t_shell *shell, t_token *redir,
			t_token *file, t_io_fd *io_fd);

bool	is_dir(char *cmd);
bool	is_builtin(char *cmd);
bool	check_heredoc(t_cmds *cmd);
bool	is_valid_pipe(t_token *s, t_token *e);
bool	handle_heredoc(t_shell *shell, t_token *limit, t_io_fd *io_fd);

char	**get_envp(t_env *env);
char	*search_cmd(char *cmd, t_shell *shell, int *ret);

int		*create_pipe_fd(t_shell *shell);
int		setup_redirect(t_io_fd *io_fd, int flags);
int		execute(t_shell *shell, t_cmds *cmd, pid_t last_pid);
int		error_message(t_shell *shell, char *cmd, bool print);

t_io_fd	*new_io_fd(void);

t_token	*get_token_end(t_token *token);

t_cmds	*built_cmd(t_token	*token, t_shell *shell);
t_cmds	*new_cmd_full(char *cmd, char **arg, int *pipe_fd, t_io_fd *io_fd);

#endif