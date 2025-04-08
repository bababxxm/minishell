/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklaokli <sklaokli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 02:01:41 by sklaokli          #+#    #+#             */
/*   Updated: 2025/04/09 02:02:21 by sklaokli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

typedef enum e_quote_type
{
	DOUBLE,
	SINGLE,
	UNQUOTED,
}	t_quote_type;

typedef enum e_token_type
{
	TK_PIPE,
	TK_REDIRECT,
	TK_COMMAND,
    TK_OPTION,
    TK_TEXT,
    TK_FILE,
    TK_EXPAND
}   t_token_type;

typedef struct s_token
{
    char                *argv;
    t_token_type        token;
	t_quote_type		quote;
    struct s_token      *next;
}   t_token;

#endif