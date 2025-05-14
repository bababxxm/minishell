/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklaokli <sklaokli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 19:19:10 by sklaokli          #+#    #+#             */
/*   Updated: 2025/05/14 21:41:40 by sklaokli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_error(t_shell *shell, int err_nb)
{
	(void)shell;
	close_fds(shell->cmds);
	free_safealloc();
	rl_clear_history();
	exit(err_nb);
}
