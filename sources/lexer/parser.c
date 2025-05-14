/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklaokli <sklaokli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 23:04:29 by sklaokli          #+#    #+#             */
/*   Updated: 2025/05/14 04:15:41 by sklaokli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	syntax_errmsg(int syntax_errno, char *text)
{
	char	*errmsg;

	errmsg = NULL;
	if (syntax_errno == UNMATCHED_QUOTE)
		errmsg = "unmatched quotes";
	else if (syntax_errno == ERROR_TOKEN)
	{
		errmsg = strappend("error near unexpected token", text);
		errmsg = strappend(errmsg, "'");
	}
	else if (syntax_errno == AMBIGUOUS)
		errmsg = strappend(text, ": ambiguous redirect");
	else if (syntax_errno == OVERFLOW)
		errmsg = "too many arguments";
	errmsg = strappend("minishell: syntax: ", errmsg);
	ft_putendl_fd(errmsg, STDERR_FILENO);
}

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

int	check_tokens(t_token *bef, t_token *cur, t_token *aft)
{
	if (!bef && cur->type == TK_PIPE)
    	return (syntax_errmsg(ERROR_TOKEN, "|"), 2);
    else if (cur->type == TK_PIPE && !aft)
        return (syntax_errmsg(ERROR_TOKEN, "|"), 2);
    else if (is_operator_token(cur) && !aft)
        return (syntax_errmsg(ERROR_TOKEN, "newline"), 2);
    else if (is_operator_token(cur) && cur->type != TK_PIPE
        && is_operator_token(aft))
        return (syntax_errmsg(ERROR_TOKEN, aft->value), 2);
	else if (is_operator_token(cur) && cur->type != TK_HEREDOC
		&& cur->type != TK_PIPE && !aft->value)
		return (syntax_errmsg(AMBIGUOUS, aft->raw), 1);
	else
		return (0);
}

bool    validate_tokens(t_shell *shell, t_token *token)
{
    t_token    *bef;
    t_token    *aft;

	if (!validate_quotes(shell->input))
	{
		shell->exit_code = 2;
		return (syntax_errmsg(UNMATCHED_QUOTE, NULL), false);
	}
	else if (!token)
        return (false);
	else if (ft_lstsize((t_list *)token) > ARGV_MAX)
	{
		shell->exit_code = 2;
		return (syntax_errmsg(OVERFLOW, NULL), false);
	}
    bef = NULL;
    aft = token->next;
    while (token)
    {
		shell->exit_code = check_tokens(bef, token, aft);
		if (shell->exit_code)
			return (false);
        bef = token;
        token = token->next;
        if (token)
            aft = token->next;
    }
    return (true);
}
