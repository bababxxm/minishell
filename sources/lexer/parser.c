/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklaokli <sklaokli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 23:04:29 by sklaokli          #+#    #+#             */
/*   Updated: 2025/05/07 00:40:18 by sklaokli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	syntax_errmsg(int _errno)
{
	if (_errno == UNMATCHED_QUOTE)
		printf("minishell: syntax: unmatched quotes\n");
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
			if (str[i++] != quote)
				return (syntax_errmsg(UNMATCHED_QUOTE), false);
		}
		else
			i++;
	}
	return (true);
}

// bool	validate_syntax(char *input)
// {
// 	int		i;
// 	int		_errno;

// 	i = -1;
// 	_errno = 0;
// 	while (input[++i])
// 	{
// 		if (input[i] == '\'' || input[i] == '\"')
// 			_errno = validate_quotes(i, input);
// 	}	
// }