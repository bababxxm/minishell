/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklaokli <sklaokli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 17:58:45 by sklaokli          #+#    #+#             */
/*   Updated: 2025/05/06 20:09:12 by sklaokli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clear_env(t_env *env, char **sort_key)
{
	t_env	*tmp;

	while (env)
	{
		tmp = env;
		env = env->next;
		free_ptr(tmp->key);
		free_ptr(tmp->value);
		free_ptr(tmp);
	}
	free_ptr(sort_key);
}

void	clear_tokens(t_token *token)
{
	t_token	*tmp;

	while (token)
	{
		tmp = token;
		token = tmp->next;
		free_ptr(tmp->value);
		free_ptr(tmp);
	}
}

void	clear_cmds(t_cmds *cmd)
{
	t_cmds	*tmp;
	int i = 0;

	tmp = cmd;
	while (cmd)
	{
		free_ptr(tmp->cmd);
		free_arg(tmp->arg);
		free_ptr(tmp->io_fd);
		free_ptr(tmp->pipe_fd);
		cmd = cmd->next;
		free_ptr(tmp);
		tmp = cmd;
	}
}

void	clear_shell(t_shell *shell)
{
	clear_env(shell->env, shell->sort_key);
	clear_cmds(shell->cmds);
	// clear_tokens(shell->token);
}
