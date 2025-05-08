/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkhienko42 <pkhienko42@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 18:21:06 by sklaokli          #+#    #+#             */
/*   Updated: 2025/05/07 23:50:26 by pkhienko42       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	skip_space(int start, char *str)
{
	int	i;

	i = start;
	while (str[i] && ft_isspace(str[i]))
		i++;
	return (i);
}

char	*join_and_free(char *s1, char *s2)
{
	char	*res;

	res = ft_strjoin(s1, s2);
	if (!res)
		return (NULL);
	return (res);
}

/*

	debug only

*/

void	print_tokens(t_token *token)
{
	if (!token)
		return ;
	printf("token:\n");
	while (token)
	{
		if (token->type == TK_PIPE)
			printf("pipe");
		else if (token->type == TK_REDIRECT_IN)
			printf("in");
		else if (token->type == TK_REDIRECT_OUT)
			printf("out");
		else if (token->type == TK_APPEND)
			printf("append");
		else if (token->type == TK_HEREDOC)
			printf("heredoc");
		else if (token->type == TK_OPTION)
			printf("option");
		else if (token->type == TK_WORD)
			printf("word");
		printf("\t| %d | %s\n", token->index, token->value);
		token = token->next;
	}
	printf("-----------------------------\n");
}
