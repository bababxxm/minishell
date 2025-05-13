#include "minishell.h"

static char	**create_arg(t_token *start, t_token *end, int *i)
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

t_cmds	*create_cmd(t_token *start, t_token *end, t_shell *shell)
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
		pipe_fd = create_pipe_fd(shell);
	else
		pipe_fd = NULL;
	io_fd = new_io_fd();
	arg = create_arg(start, end, &e);
	while (is_valid_pipe(start, end))
	{
		if (start->type >= TK_REDIRECT_IN && start->type <= TK_HEREDOC)
		{
			handle_redirection(shell, start, start->next, io_fd);
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

t_cmds	*built_cmd(t_token	*token, t_shell *shell)
{
	t_cmds	*head;
	t_cmds	*tail;
	t_cmds	*new;

	new = NULL;
	head = NULL;
	tail = NULL;
	while (token && !token->value)
		token = token->next;
	while (token)
	{
		new = create_cmd(token, get_token_end(token), shell);
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
