/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklaokli <sklaokli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 21:58:23 by sklaokli          #+#    #+#             */
/*   Updated: 2025/05/14 21:58:47 by sklaokli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_exitcode(char *oldprompt, int *exitcode)
{
	int		i;
	char	*newprompt;

	i = 0;
	while (oldprompt[i] && oldprompt[i] != ' ')
		i++;
	*exitcode = 130;
	newprompt = strappend(B_YELLOW"["B_RED, ft_itoa(130));
	newprompt = strappend(newprompt, B_YELLOW"]"B_RED);
	newprompt = strappend(newprompt, &oldprompt[i]);
	oldprompt = "";
	return (newprompt);
}

char	*get_prompt(t_shell *shell)
{
	char			*path;
	static char		*prompt;
	static int		*exitcode;

	if (!shell)
		return (get_exitcode(prompt, exitcode));
	exitcode = &shell->exit_code;
	if (shell->exit_code == 0)
		prompt = strappend(B_YELLOW"["B_GREEN, ft_itoa(shell->exit_code));
	else
		prompt = strappend(B_YELLOW"["B_RED, ft_itoa(shell->exit_code));
	prompt = strappend(prompt, B_YELLOW"] "B_RED);
	prompt = strappend(prompt, ft_strdup(shell->user));
	if (!ft_strncmp(shell->home, shell->pwd, ft_strlen(shell->home)))
		path = strappend("~", ft_strdup(shell->pwd + ft_strlen(shell->home)));
	else
		path = ft_strdup(shell->pwd);
	prompt = strappend(prompt, B_YELLOW":"B_GREEN);
	prompt = strappend(prompt, path);
	prompt = strappend(prompt, B_YELLOW"$ "RESET);
	return (prompt);
}
