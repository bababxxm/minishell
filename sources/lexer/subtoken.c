/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subtoken.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkhienko42 <pkhienko42@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 18:21:08 by sklaokli          #+#    #+#             */
/*   Updated: 2025/05/07 23:53:31 by pkhienko42       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	add_subtoken_index(int i, char *str, int index)
{
	if (ft_isspace(str[i]))
		index++;
	else if (is_operator(str[i]))
		index++;
	else if (is_operator(str[i - 1]) && !is_operator(str[i]))
		index++;
	return (index);
}

int	token_strlen(t_token *subtoken, int index)
{
	int	len;

	len = 0;
	while (subtoken && subtoken->index == index)
	{
		len += ft_strlen(subtoken->value);
		subtoken = subtoken->next;
	}
	return (len);
}

void	token_strjoin(t_token **token, t_token *subtoken, int len, int index)
{
	int		i;
	int		j;
	int		type;
	char	*join;

	if (len <= 0)
	{
		add_token(index, NULL, TK_WORD, token);
		return ;
	}
	join = safealloc(len + 1, sizeof(char));
	if (!join)
		return ;
	i = 0;
	type = subtoken->type;
	while (subtoken && subtoken->index == index)
	{
		j = 0;
		while (subtoken->value && subtoken->value[j])
			join[i++] = subtoken->value[j++];
		subtoken = subtoken->next;
	}
	join[i] = '\0';
	add_token(index, join, type, token);
}

t_token	*merge_subtokens(t_token *subtoken)
{
	int		len;
	int		index;
	t_token	*token;

	index = 0;
	token = NULL;
	while (subtoken)
	{
		while (subtoken && subtoken->index != index)
			subtoken = subtoken->next;
		if (!subtoken)
			break ;
		len = token_strlen(subtoken, index);
		token_strjoin(&token, subtoken, len, index++);
	}
	return (token);
}
