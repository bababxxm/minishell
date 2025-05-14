/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklaokli <sklaokli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 21:59:49 by sklaokli          #+#    #+#             */
/*   Updated: 2025/05/15 03:46:04 by sklaokli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	syntax_errmsg(int syntax_errno, char *text);

bool	validate_quotes(char *str)
{
	int		i;
	char	quote;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			quote = str[i++];
			while (str[i] && str[i] != quote)
				i++;
			if (!str[i] || str[i++] != quote)
				return (false);
		}
		else
			i++;
	}
	return (true);
}

bool	is_operator_token(t_token *token)
{
	if (!token)
		return (false);
	return (token->type == TK_PIPE
		|| token->type == TK_REDIRECT_IN
		|| token->type == TK_REDIRECT_OUT
		|| token->type == TK_HEREDOC
		|| token->type == TK_APPEND);
}

bool	check_tokens_3(t_shell *shell, t_token *bef, t_token *cur, t_token *aft)
{
	(void)bef;
	if (is_operator_token(cur) && cur->type != TK_PIPE
		&& is_operator_token(aft))
	{
		shell->exit_code = 2;
		return (syntax_errmsg(ERROR_TOKEN, aft->value), false);
	}
	else if (is_operator_token(cur) && cur->type != TK_HEREDOC
		&& cur->type != TK_PIPE && !aft->raw)
	{
		shell->exit_code = 1;
		return (syntax_errmsg(ERROR_TOKEN, aft->raw), false);
	}
	else
		return (true);
}

bool	check_tokens_2(t_shell *shell, t_token *bef, t_token *cur, t_token *aft)
{
	if (!bef && cur->type == TK_PIPE)
	{
		shell->exit_code = 2;
		return (syntax_errmsg(ERROR_TOKEN, "|"), false);
	}
	else if (cur->type == TK_PIPE && !aft)
	{
		shell->exit_code = 2;
		return (syntax_errmsg(ERROR_TOKEN, "|"), false);
	}
	else if (is_operator_token(cur) && !aft)
	{
		shell->exit_code = 2;
		return (syntax_errmsg(ERROR_TOKEN, "newline"), false);
	}
	else if (!check_tokens_3(shell, bef, cur, aft))
	{
		return (false);
	}
	return (true);
}

bool	check_tokens_1(t_shell *shell, t_token *token)
{
	if (!validate_quotes(shell->input))
	{
		shell->exit_code = 0;
		return (syntax_errmsg(UNMATCHED_QUOTE, NULL), false);
	}
	else if (!token)
		return (false);
	else if (ft_lstsize((t_list *)token) > ARGV_MAX)
	{
		shell->exit_code = 0;
		return (syntax_errmsg(OVERFLOW, NULL), false);
	}
	return (true);
}
