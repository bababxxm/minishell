/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkhienko42 <pkhienko42@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 18:40:43 by sklaokli          #+#    #+#             */
/*   Updated: 2025/05/09 02:16:51 by pkhienko42       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

typedef enum e_syntax_status
{
	UNMATCHED_QUOTE,
	ERROR_TOKEN
}	t_syntax_status;

typedef enum e_token_type
{
	TK_PIPE,
	TK_REDIRECT_IN,
	TK_REDIRECT_OUT,
	TK_APPEND,
	TK_HEREDOC,
	TK_OPTION,
	TK_WORD
}	t_token_type;

typedef struct s_token
{
	struct s_token		*next;
	int					index;
	char				*value;
	t_token_type		type;
}	t_token;

bool	validate_quotes(char *str);
bool	validate_tokens(t_token *token);

bool	is_operator(char c);
int		handle_quotes(int start, t_shell *shell, int index, t_token **token);
int		handle_operators(int start, t_shell *shell, int index, t_token **token);
int		handle_unquotes(int start, t_shell *shell, int index, t_token **token);

bool	has_expand(char *str);
int		var_length(char *str);
char	*ft_expand(char *str, int *ptr, t_env *env, t_shell *shell);
char	*cut_invalid_expand(char *str);
char	*expand_variable(char *str, t_env *env, t_shell *shell);

int		add_subtoken_index(int i, char *str, int index);
int		token_strlen(t_token *subtoken, int index);
void	token_strjoin(t_token **token, t_token *subtoken, int len, int index);
t_token	*merge_subtokens(t_token *subtoken);

t_token	*new_token(int index, char *value, int type);
void	add_token(int index, char *value, short type, t_token **token);
t_token	*tokenizer(t_shell *shell);

int		skip_space(int start, char *str);
char	*join_and_free(char *s1, char *s2);
void	print_tokens(t_token *token);

#endif