/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkhienko42 <pkhienko42@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 00:55:17 by sklaokli          #+#    #+#             */
/*   Updated: 2025/05/07 23:49:35 by pkhienko42       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_export(char *cmd)
{
	if (!ft_strncmp(cmd, "export", 6))
		return (true);
	return (false);
}

int	errmsg_cmd(char *cmd, char *detail, char *err_msg, int err_nb)
{
	char	*msg;
	bool	export;

	export = is_export(cmd);
	msg = ft_strdup("minishell: ");
	if (cmd)
	{
		msg = safe_strjoin(msg, cmd);
		msg = safe_strjoin(msg, ": ");
	}
	if (detail)
	{
		if (export)
			msg = safe_strjoin(msg, "`");
		msg = safe_strjoin(msg, detail);
		if (export)
			msg = safe_strjoin(msg, "'");
		msg = safe_strjoin(msg, ": ");
	}
	if (err_msg)
		msg = safe_strjoin(msg, err_msg);
	ft_putendl_fd(msg, STDERR_FILENO);
	return (err_nb);
}
