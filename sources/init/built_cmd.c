/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklaokli <sklaokli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 21:48:10 by sklaokli          #+#    #+#             */
/*   Updated: 2025/05/15 01:14:25 by sklaokli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**create_arg(t_token *start, t_token *end, int *i)
{
	char	**arg;

	while (start && (start != end || start->type != TK_PIPE))
	{
		(*i)++;
		start = start->next;
	}
	arg = safealloc(*i + 1, sizeof(char *));
	return (arg);
}

static int	*set_new_io_pipe(t_token *end, t_shell *shell, t_io_fd **io_fd)
{
	int	*pipe_fd;

	*io_fd = new_io_fd();
	if (end && end->type == TK_PIPE)
		pipe_fd = create_pipe_fd(shell);
	else
		pipe_fd = NULL;
	return (pipe_fd);
}

static t_token	*set_new_redir(t_token *start, t_io_fd *io_fd, t_shell *shell)
{
	handle_redirection(shell, start, start->next, io_fd);
	start = start->next;
	return (start);
}

t_cmds	*create_cmd(t_token *start, t_token *end, t_shell *shell, int s)
{
	char	*cmd;
	char	**arg;
	int		*pipe_fd;
	int		e;
	t_io_fd	*io_fd;

	e = 0;
	cmd = NULL;
	pipe_fd = set_new_io_pipe(end, shell, &io_fd);
	arg = create_arg(start, end, &e);
	while (is_valid_pipe(start, end))
	{
		if (start->type >= TK_REDIRECT_IN && start->type <= TK_HEREDOC)
			start = set_new_redir(start, io_fd, shell);
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
		new = create_cmd(token, get_token_end(token), shell, 0);
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
