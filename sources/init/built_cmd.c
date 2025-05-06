#include "minishell.h"

static t_io_fd	*new_io_fd()
{
	t_io_fd	*io_fd;

	io_fd = safe_malloc(sizeof(t_io_fd));
	if (!io_fd)
		return (NULL);
	io_fd->heredoc = NULL;
	io_fd->in_file = NULL;
	io_fd->out_file = NULL;
	io_fd->fd_in = -1;
	io_fd->fd_out = -1;
	io_fd->stdin_backup = -1;
	io_fd->stdout_backup = -1;
	return (io_fd);
}

static t_cmds	*new_cmd(char *cmd, char **arg, int *pipe_fd)
{
	t_cmds	*command;

	command = safe_malloc(sizeof(t_cmds));
	if (!command)
		return (NULL);
	command->cmd = cmd;
	command->arg = arg;
	command->pipe_fd = pipe_fd;
	command->io_fd = new_io_fd();
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

char	*search_cmd(char *cmd, t_shell *shell)
{
	char	**all_path;
	char	*select_path;
	char	*new_cmd;

	int		i;

	i = -1;
	all_path = ft_split(get_value(shell->env, "PATH"), ':');
	while (all_path[++i])
	{
		select_path = ft_strjoin(all_path[i], "/");
		new_cmd = ft_strjoin(select_path, cmd);
		free_ptr(select_path);
		if (!access(new_cmd, F_OK | X_OK))
		{
			free_arg(all_path);
			return (new_cmd);
		}
		free_ptr(new_cmd);
	}
	free_arg(all_path);
	if (access(cmd, F_OK | X_OK) == -1)
		errmsg_cmd(cmd, NULL, "command not found", EXIT_FAILURE);
	return (ft_strdup(cmd));
}

char	**create_arg(t_token *start, t_token *end, int *i)
{
	char	**arg;
	
	while (start &&(start != end || start->type != TK_PIPE))
	{
		(*i)++;
		start = start->next;
	}
	arg = safe_malloc(sizeof(char *) * (*i + 1));
	if (!arg)
		return (NULL);
	return (arg);
}

t_cmds	*create_cmd(t_token	*start, t_token *end, t_cmds *head, t_shell *shell)
{
	char	*cmd;
	char	**arg;
	int		*pipe_fd;
	int		s;
	int		e;

	s = 0;
	e = 0;
	cmd = NULL;
	arg = create_arg(start, end, &e);
	pipe_fd = NULL;
	while (start && (start != end || start->type != TK_PIPE))
	{
		if (!cmd)
			cmd = search_cmd(start->value, shell);
		if (s < e)
			arg[s++] = ft_strdup(start->value);
		start = start->next;
	}
	arg[s] = NULL;
	if (end->type == TK_PIPE || (head->prev && head->prev->pipe_fd))
		pipe_fd = create_pipe_fd();
	return (new_cmd(cmd, arg, pipe_fd));
}

t_cmds	*built_cmd(t_shell *shell, t_token	*token)
{
	t_cmds	*head;
	t_cmds	*tail;
	t_cmds	*new;

	new = NULL;
	head = NULL;
	tail = NULL;
	while (token)
	{

		new = create_cmd(token, get_token_end(token), head, shell);
		token = get_token_end(token);
		if (!new)
			return (NULL);
		if (!head)
			head = new;
		else
			tail->next = new;
		head->prev = tail;
		tail = new;
		token = token->next;
	}
	return (head);
}
