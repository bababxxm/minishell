/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkhienko42 <pkhienko42@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 22:16:47 by pkhienko          #+#    #+#             */
/*   Updated: 2025/05/07 23:34:22 by pkhienko42       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	issep(char const *s, char c)
{
	int	sep;

	if (!s)
		return (0);
	sep = 0;
	while (*s)
	{
		if (*s != c && (*(s + 1) == c || *(s + 1) == '\0'))
			sep++;
		s++;
	}
	return (sep);
}

static int	len(char const *s, char c)
{
	int	len;

	if (!s)
		return (0);
	len = 0;
	while (*s && *s != c)
	{
		len++;
		s++;
	}
	return (len);
}

static char	**freesplit(char **str, int nb)
{
	while (nb >= 0)
		free(str[nb--]);
	free(str);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**str;
	int		start;
	int		idx;

	if (!s)
		return (NULL);
	str = (char **)safealloc(issep(s, c) + 1, sizeof(char *));
	if (!str)
		return (NULL);
	start = 0;
	idx = 0;
	while (s[start])
	{
		if (s[start] != c)
		{
			str[idx] = ft_substr(s, start, len(&s[start], c));
			if (!str[idx++])
				return (freesplit(str, idx));
			start += len(&s[start], c);
		}
		else
			start++;
	}
	str[idx] = 0;
	return (str);
}
