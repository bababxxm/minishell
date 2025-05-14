/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklaokli <sklaokli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 23:04:29 by sklaokli          #+#    #+#             */
/*   Updated: 2025/05/14 22:10:06 by sklaokli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	check_tokens_1(t_shell *shell, t_token *token);
bool	check_tokens_2(t_shell *shell, t_token *bef,
			t_token *cur, t_token *aft);
bool	check_tokens_3(t_shell *shell, t_token *bef,
			t_token *cur, t_token *aft);

void	syntax_errmsg(int syntax_errno, char *text)
{
	char	*errmsg;

	errmsg = NULL;
	if (syntax_errno == UNMATCHED_QUOTE)
		errmsg = "unmatched quotes";
	else if (syntax_errno == ERROR_TOKEN)
	{
		errmsg = strappend("error near unexpected token '", text);
		errmsg = strappend(errmsg, "'");
	}
	else if (syntax_errno == AMBIGUOUS)
		errmsg = strappend(text, ": ambiguous redirect");
	else if (syntax_errno == OVERFLOW)
		errmsg = "too many arguments";
	errmsg = strappend("minishell: syntax: ", errmsg);
	ft_putendl_fd(errmsg, STDERR_FILENO);
}

bool	validate_tokens(t_shell *shell, t_token *token)
{
	t_token	*bef;
	t_token	*aft;

	if (!check_tokens_1(shell, token))
		return (false);
	bef = NULL;
	aft = token->next;
	while (token)
	{
		if (!check_tokens_2(shell, bef, token, aft))
			return (false);
		if (!check_tokens_3(shell, bef, token, aft))
			return (false);
		bef = token;
		token = token->next;
		if (token)
			aft = token->next;
	}
	return (true);
}
