/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklaokli <sklaokli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 00:55:17 by sklaokli          #+#    #+#             */
/*   Updated: 2025/05/15 01:43:29 by sklaokli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_export(char *cmd)
{
	if (!ft_strncmp(cmd, "export", 6))
		return (true);
	return (false);
}

int	errmsg(char *cmd, char *detail, char *err_msg, int err_nb)
{
	char	*msg;
	bool	export;

	export = is_export(cmd);
	msg = ft_strdup("minishell: ");
	if (cmd)
	{
		msg = strappend(msg, cmd);
		msg = strappend(msg, ": ");
	}
	if (detail)
	{
		if (export)
			msg = strappend(msg, "`");
		msg = strappend(msg, detail);
		if (export)
			msg = strappend(msg, "'");
		msg = strappend(msg, ": ");
	}
	if (err_msg)
		msg = strappend(msg, err_msg);
	ft_putendl_fd(msg, STDERR_FILENO);
	return (err_nb);
}

static int	print_error(t_shell *shell, char *cmd, int fd)
{
	if (!ft_strncmp("~", cmd, -1) && ft_strlen(cmd) == 1)
		return (errmsg(shell->home, NULL, "Is a directory",
				CMD_NOT_EXECUTABLE));
	if (!ft_strchr(cmd, '/'))
	{
		if (fd >= 0)
			close(fd);
		return (errmsg(cmd, NULL, "command not found", CMD_NOT_FOUND));
	}
	else if (fd == -1 && !is_dir(cmd))
		return (errmsg(cmd, NULL, "No such file or directory", CMD_NOT_FOUND));
	else if (fd == -1 && is_dir(cmd))
		return (errmsg(cmd, NULL, strerror(errno), CMD_NOT_EXECUTABLE));
	else if (fd != -1 && !is_dir(cmd))
	{
		close(fd);
		return (errmsg(cmd, NULL, "Permission denied", CMD_NOT_EXECUTABLE));
	}
	return (EXIT_SUCCESS);
}

static int	non_print_error(char *cmd, int fd)
{
	if (!ft_strchr(cmd, '/'))
	{
		if (fd >= 0)
			close(fd);
		return (CMD_NOT_FOUND);
	}
	else if (fd == -1 && !is_dir(cmd))
		return (CMD_NOT_EXECUTABLE);
	else if (fd == -1 && is_dir(cmd))
		return (CMD_NOT_EXECUTABLE);
	else if (fd != -1 && !is_dir(cmd))
	{
		close(fd);
		return (CMD_NOT_EXECUTABLE);
	}
	return (EXIT_SUCCESS);
}

int	error_message(t_shell *shell, char *cmd, bool print)
{
	int	fd;

	fd = open(cmd, O_WRONLY);
	if (print)
		return (print_error(shell, cmd, fd));
	else
		return (non_print_error(cmd, fd));
	if (fd >= 0)
		close(fd);
	return (EXIT_SUCCESS);
}
