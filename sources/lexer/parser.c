/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkhienko42 <pkhienko42@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 23:04:29 by sklaokli          #+#    #+#             */
/*   Updated: 2025/05/07 23:52:06 by pkhienko42       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	syntax_errmsg(int syntax_errno, char *text)
{
	if (syntax_errno == UNMATCHED_QUOTE)
		printf("minishell: syntax: unmatched quotes\n");
	else if (syntax_errno == ERROR_TOKEN && text)
		printf("minishell: syntax: error near unexpected token '%s'\n", text);
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
				return (syntax_errmsg(UNMATCHED_QUOTE, NULL), false);
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

bool	validate_tokens(t_token *token)
{
	t_token	*before;
	t_token	*after;

	if (!token)
		return (false);
	before = NULL;
	after = token->next;
	while (token)
	{
		if (!before && token->type == TK_PIPE)
			return (syntax_errmsg(ERROR_TOKEN, "|"), false);
		else if (token->type == TK_PIPE && !after)
			return (syntax_errmsg(ERROR_TOKEN, "|"), false);
		else if (is_operator_token(token) && !after)
			return (syntax_errmsg(ERROR_TOKEN, "newline"), false);
		else if (is_operator_token(token) && is_operator_token(after))
			return (syntax_errmsg(ERROR_TOKEN, after->value), false);
		before = token;
		token = token->next;
		if (token)
			after = token->next;
	}
	return (true);
}
