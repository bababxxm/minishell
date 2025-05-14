/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklaokli <sklaokli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 18:26:05 by sklaokli          #+#    #+#             */
/*   Updated: 2025/05/14 22:03:21 by sklaokli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_operator(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

char	**set_data(char *raw, char *value)
{
	char	**data;

	data = safealloc(2, sizeof(char *));
	data[0] = raw;
	data[1] = value;
	return (data);
}

int	handle_quotes(int start, t_shell *shell,\
	int index, t_token **token)
{
	int		end;
	char	quote;
	char	*raw;
	char	*str;

	end = start;
	quote = shell->input[end++];
	while (shell->input[end] && shell->input[end] != quote)
		end++;
	if (!shell->input[end])
		return (end);
	raw = ft_substr(shell->input, start + 1, end - start - 1);
	str = ft_strdup(raw);
	if (quote == '\"' && has_expand(str))
		str = expand_variable(str, shell->env, shell);
	if (!str)
		add_token(index, set_data(raw, ft_strdup("")), TK_WORD, token);
	else if (str[0] == '-' && str[1])
		add_token(index, set_data(raw, str), TK_OPTION, token);
	else
		add_token(index, set_data(raw, str), TK_WORD, token);
	return (end + 1);
}

int	handle_unquotes(int start, t_shell *shell,\
	int index, t_token **token)
{
	int		end;
	char	*raw;
	char	*str;

	end = start;
	while (shell->input[end] && !ft_isspace(shell->input[end])
		&& shell->input[end] != '\'' && shell->input[end] != '\"'
		&& !is_operator(shell->input[end]))
		end++;
	raw = ft_substr(shell->input, start, end - start);
	str = ft_strdup(raw);
	if (has_expand(str))
		str = expand_variable(str, shell->env, shell);
	if (shell->input[end - 1] == '$'
		&& (shell->input[end] == '\'' || shell->input[end] == '\"'))
		str = cut_invalid_expand(str);
	if (!str)
		add_token(index, set_data(raw, str), TK_WORD, token);
	else if (str[0] == '-' && str[1])
		add_token(index, set_data(raw, str), TK_OPTION, token);
	else
		add_token(index, set_data(raw, str), TK_WORD, token);
	return (end);
}

int	handle_operators(int start, t_shell *shell,\
	int index, t_token **token)
{
	if (shell->input[start] == '<' && shell->input[start + 1] == '<')
		return (add_token(index, set_data(
					ft_substr(shell->input, start, 2),
					ft_substr(shell->input, start, 2)),
				TK_HEREDOC, token), start + 2);
	else if (shell->input[start] == '>' && shell->input[start + 1] == '>')
		return (add_token(index, set_data(
					ft_substr(shell->input, start, 2),
					ft_substr(shell->input, start, 2)),
				TK_APPEND, token), start + 2);
	else if (shell->input[start] == '<')
		return (add_token(index, set_data(
					ft_substr(shell->input, start, 1),
					ft_substr(shell->input, start, 1)),
				TK_REDIRECT_IN, token), start + 1);
	else if (shell->input[start] == '>')
		return (add_token(index, set_data(
					ft_substr(shell->input, start, 1),
					ft_substr(shell->input, start, 1)),
				TK_REDIRECT_OUT, token), start + 1);
	else
		return (add_token(index, set_data(
					ft_substr(shell->input, start, 1),
					ft_substr(shell->input, start, 1)),
				TK_PIPE, token), start + 1);
}
