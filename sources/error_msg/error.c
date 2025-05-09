/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkhienko42 <pkhienko42@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 00:55:17 by sklaokli          #+#    #+#             */
/*   Updated: 2025/05/09 17:12:22 by pkhienko42       ###   ########.fr       */
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

// to do
int	cmd_not_found(t_cmds *cmd, char *c, bool only_not_found)
{
	(void)c;

	if ((!ft_strncmp(cmd->cmd, ".", 1) || !ft_strncmp(cmd->cmd, "/", 1)) && access(cmd->cmd, F_OK) == -1)
		return (errmsg(cmd->cmd, NULL, "command not found", CMD_NOT_FOUND));
	if (access(cmd->cmd, F_OK) == -1 && only_not_found)
		return (errmsg(cmd->cmd, NULL, strerror(errno), CMD_NOT_FOUND));
	if (is_dir(cmd->cmd) && only_not_found)
		return (errmsg(cmd->cmd, NULL, "Is a directory", CMD_NOT_EXECUTABLE));
	if (access(cmd->cmd, X_OK) == -1 && only_not_found)
		return (errmsg(cmd->cmd, NULL, strerror(errno), CMD_NOT_EXECUTABLE));
	return (EXIT_SUCCESS);
}
