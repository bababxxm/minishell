/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklaokli <sklaokli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 04:08:50 by sklaokli          #+#    #+#             */
/*   Updated: 2025/04/19 21:40:36 by sklaokli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*new_token(char *argv, t_token_type tk_type, t_quote_type qt_type)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->argv = argv;
	new->tk_type = tk_type;
	new->qt_type = qt_type;
	new->next = NULL;
	return (new);
}

t_token_type	get_token_type(char *argv)
{
	if (argv[0] == '|' && argv[1] == '\0')
		return (TK_PIPE);
	if (argv[0] == '>' || !ft_strncmp(argv, ">>", 2) ||
		argv[0] == '<' || !ft_strncmp(argv, "<<", 2))
		return (TK_REDIRECT);
	if (argv[0] == '-' && argv[1])
		return (TK_OPTION);
	if (argv[0] == '$' && argv[1])
		return (TK_EXPAND);
	if (!ft_strncmp("\\", argv, ft_strlen(argv)))
		return (TK_COMMAND);
	if (!ft_strncmp("\\", argv, ft_strlen(argv)))
		return (TK_FILE);
}

t_quote_type	get_quote_type(char *argv)
{
	
}

t_token	*get_tokens(char *input)
{
	int		i;
	t_token	tmp;
	t_token	*tokens;

	i = -1;
	while (input[++i])
	{
		while (input[i] && input[i] == ' ')
			i++;
		tmp.argv = &input[i];
		while (input[i] && input[i] != ' ')
			i++;
		input[i] = '\0';
		printf("%s\n", tmp.argv);
		ft_lstadd_back((void *)&tokens, new_token(tmp.argv, \
			get_token_type(tmp.argv), get_quote_type(tmp.argv)));
	}
	return (NULL);
}
