/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklaokli <sklaokli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 18:40:43 by sklaokli          #+#    #+#             */
/*   Updated: 2025/05/14 03:43:01 by sklaokli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

typedef enum e_syntax_status
{
	UNMATCHED_QUOTE,
	ERROR_TOKEN,
	AMBIGUOUS,
	OVERFLOW
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
	char				*raw;
	char				*value;
	t_token_type		type;
}	t_token;

void	print_tokens(t_token *token);
void	add_token(int index, char **str, short type, t_token **token);

bool	is_operator(char c);
bool	has_expand(char *str);
bool	validate_quotes(char *str);
bool	validate_tokens(t_shell *shell, t_token *token);
bool	token_strjoin(t_token **token, t_token *subtoken, int index);

char	*cut_invalid_expand(char *str);
char	*join_and_free(char *s1, char *s2);
char	*expand_variable(char *str, t_env *env, t_shell *shell);
char	*ft_expand(char *str, int *ptr, t_env *env, t_shell *shell);

int		var_length(char *str);
int		skip_space(int start, char *str);
int		token_strlen(t_token *subtoken, int index);
int		add_subtoken_index(int i, char *str, int index);
int		handle_quotes(int start, t_shell *shell, int index, t_token **token);
int		handle_unquotes(int start, t_shell *shell, int index, t_token **token);
int		handle_operators(int start, t_shell *shell, int index, t_token **token);

t_token	*tokenizer(t_shell *shell);
t_token	*merge_subtokens(t_token *subtoken);
t_token	*new_token(int index, char *raw, char *value, int type);

#endif