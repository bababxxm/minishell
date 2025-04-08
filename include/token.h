/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklaokli <sklaokli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 02:01:41 by sklaokli          #+#    #+#             */
/*   Updated: 2025/04/09 06:07:45 by sklaokli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

typedef enum e_quote_type
{
	QT_DOUBLE,
	QT_SINGLE,
	QT_UNQUOTED
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
    struct s_token      *next;
    char                *argv;
    t_token_type        tk_type;
	t_quote_type		qt_type;
}   t_token;

#endif