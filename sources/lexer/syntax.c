/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkhienko42 <pkhienko42@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 18:26:05 by sklaokli          #+#    #+#             */
/*   Updated: 2025/05/09 02:20:34 by pkhienko42       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_operator(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

int	handle_quotes(int start, t_shell *shell,\
	int index, t_token **token)
{
	int		end;
	char	quote;
	char	*str;

	end = start;
	quote = shell->input[end++];
	while (shell->input[end] && shell->input[end] != quote)
		end++;
	if (!shell->input[end])
		return (end);
	str = ft_substr(shell->input, start + 1, end - start - 1);
	if (quote == '\"' && has_expand(str))
		str = expand_variable(str, shell->env, shell);
	if (!str)
		add_token(index, str, TK_WORD, token);
	else if (str[0] == '-' && str[1])
		add_token(index, str, TK_OPTION, token);
	else
		add_token(index, str, TK_WORD, token);
	return (end + 1);
}

int	handle_unquotes(int start, t_shell *shell,\
	int index, t_token **token)
{
	int		end;
	char	*str;

	end = start;
	while (shell->input[end] && !ft_isspace(shell->input[end])
		&& shell->input[end] != '\'' && shell->input[end] != '\"'
		&& !is_operator(shell->input[end]))
		end++;
	str = ft_substr(shell->input, start, end - start);
	if (has_expand(str))
		str = expand_variable(str, shell->env, shell);
	if (shell->input[end - 1] == '$'
		&& (shell->input[end] == '\'' || shell->input[end] == '\"'))
		str = cut_invalid_expand(str);
	if (!str)
		add_token(index, str, TK_WORD, token);
	else if (str[0] == '-' && str[1])
		add_token(index, str, TK_OPTION, token);
	else
		add_token(index, str, TK_WORD, token);
	return (end);
}

int	handle_operators(int start, t_shell *shell,\
	int index, t_token **token)
{
	if (shell->input[start] == '<' && shell->input[start + 1] == '<')
		return (add_token(index, ft_substr(shell->input, start, 2),
				TK_HEREDOC, token), start + 2);
	else if (shell->input[start] == '>' && shell->input[start + 1] == '>')
		return (add_token(index, ft_substr(shell->input, start, 2),
				TK_APPEND, token), start + 2);
	else if (shell->input[start] == '<')
		return (add_token(index, ft_substr(shell->input, start, 1),
				TK_REDIRECT_IN, token), start + 1);
	else if (shell->input[start] == '>')
		return (add_token(index, ft_substr(shell->input, start, 1),
				TK_REDIRECT_OUT, token), start + 1);
	else
		return (add_token(index, ft_substr(shell->input, start, 1),
				TK_PIPE, token), start + 1);
}
