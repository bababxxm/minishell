/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subtoken.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkhienko42 <pkhienko42@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 18:21:08 by sklaokli          #+#    #+#             */
/*   Updated: 2025/05/13 17:41:37 by pkhienko42       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**set_data(char *raw, char *value);

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

bool	token_strjoin(t_token **token, t_token *subtoken, int index)
{
	int		type;
	char	*raw;
	char	*value;

	raw = "";
	value = "";
	type = subtoken->type;
	while (subtoken && subtoken->index == index)
	{
		raw = strappend(raw, subtoken->raw);
		value = strappend(value, subtoken->value);
		subtoken = subtoken->next;
	}
	return (add_token(index, set_data(raw, value), type, token), true);
}

t_token	*merge_subtokens(t_token *subtoken)
{
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
		token_strjoin(&token, subtoken, index++);
	}
	return (token);
}