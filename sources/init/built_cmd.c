#include "minishell.h"

static t_io_fd	*new_io_fd()
{
	t_io_fd	*io_fd;

	io_fd = safealloc(1, sizeof(t_io_fd));
	io_fd->in_file = NULL;
	io_fd->out_file = NULL;
	io_fd->heredoc = false;
	io_fd->append = false;
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


t_token	*get_token_end(t_token *token)
{
	t_token	*cur;

	cur = token;
	while (cur)
	{
		if (cur->type == TK_PIPE)
			break ;
		if (!cur->next)
			break ;
		cur = cur->next;
	}
	return (cur);
}

void	handle_redirection(t_token *redir, t_token *file, t_io_fd *io_fd)
{
	if (!file || file->type != TK_WORD)
	{
		errmsg(redir->value, NULL, "missing file for redirection", 1);
		return ;
	}
	if (redir->type == TK_REDIRECT_IN)
		io_fd->in_file = ft_strdup(file->value);
	else if (redir->type == TK_REDIRECT_OUT)
	{
		io_fd->out_file = ft_strdup(file->value);
		io_fd->append = false;
	}
	else if (redir->type == TK_APPEND)
	{
		io_fd->out_file = ft_strdup(file->value);
		io_fd->append = true;
	}
	else if (redir->type == TK_HEREDOC)
		io_fd->heredoc = handle_heredoc(file, io_fd);
}

char	**create_arg(t_token *start, t_token *end, int *i)
{
	char	**arg;
	
	while (start &&(start != end || start->type != TK_PIPE))
	{
		(*i)++;
		start = start->next;
	}
	arg = safealloc(*i + 1, sizeof(char *));
	return (arg);
}


static inline bool	is_valid_pipe(t_token *s, t_token *e)
{
	return (s && (s != e || s->type != TK_PIPE));
}

t_cmds	*create_cmd(t_token *start, t_token *end)
{
	char	*cmd;
	char	**arg;
	int		*pipe_fd;
	int		s;
	int		e;
	t_io_fd	*io_fd;

	s = 0;
	e = 0;
	cmd = NULL;
	if (end && end->type == TK_PIPE)
		pipe_fd = create_pipe_fd();
	else
		pipe_fd = NULL;
	io_fd = new_io_fd();
	arg = create_arg(start, end, &e);
	while (is_valid_pipe(start, end))
	{
		if (start->type >= TK_REDIRECT_IN && start->type <= TK_HEREDOC)
		{
			handle_redirection(start, start->next, io_fd);
			start = start->next;
		}
		else
		{
			if (!cmd && start->type == TK_WORD && s == 0)
				cmd = ft_strdup(start->value);
			if (s < e)
				arg[s++] = ft_strdup(start->value);
		}
		start = start->next;
	}
	arg[s] = NULL;
	return (new_cmd_full(cmd, arg, pipe_fd, io_fd));
}


t_cmds	*built_cmd(t_token	*token)
{
	t_cmds	*head;
	t_cmds	*tail;
	t_cmds	*new;

	new = NULL;
	head = NULL;
	tail = NULL;
	while (token)
	{

		new = create_cmd(token, get_token_end(token));
		token = get_token_end(token);
		if (!new)
			return (NULL);
		if (!head)
			head = new;
		else
			tail->next = new;
		new->prev = tail;
		tail = new;
		token = token->next;
	}
	return (head);
}
