/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklaokli <sklaokli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 18:22:50 by sklaokli          #+#    #+#             */
/*   Updated: 2025/04/09 05:14:34 by sklaokli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <signal.h>
# include <errno.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>

# include "token.h"
# include "command.h"

# define GREEN "\033[0;32m"
# define CYAN "\033[0;36m"
# define RESET "\033[0m"

# define PROMPT GREEN"➜ "RESET

typedef struct s_list
{
	struct s_list	*next;
}   t_list;

typedef struct s_env
{
	struct s_env	*next;
	char			*key;
	char			equal;
	char			*value;
}	t_env;

typedef struct s_shell
{
	char			*input;
	char			*path;
	char			*user;
	char			*home;
	char			*oldpwd;
	char			*pwd;
	t_env			*env;
	t_token			*tokens;
	t_cmds			*cmds;
	int				exit_code;			
}	t_shell;

// utils
int		ft_strlen(char *str);
int		ft_strlen_to_c(char *str, char c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strdup(char *src);
void	*last_node(void *node);
void	node_addback(void **node, void *new);

// env
t_env	*new_env(char *key, char equal, char *value);
char	*dup_var(char *str, char c);
t_env	*dup_env(char *env[]);
char	*search_env(char *key, t_env *env);
void	clear_env(t_env *env);

// token
t_token	*get_tokens(char *input);

// debug
void	print_env(t_env *env);

#endif