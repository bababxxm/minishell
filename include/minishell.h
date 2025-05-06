/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklaokli <sklaokli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 18:22:50 by sklaokli          #+#    #+#             */
/*   Updated: 2025/05/07 01:28:37 by sklaokli         ###   ########.fr       */
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

# include "libft.h"
# include "env.h"
# include "lexer.h"
# include "builtin.h"
# include "command.h"

# define YELLOW "\033[0;33m"
# define GREEN "\033[0;32m"
# define CYAN "\033[0;36m"
# define RED "\033[0;31m"
# define RESET "\033[0m"

# define PROMPT "minishell$ "

# ifndef PATH_MAX
#  define PATH_MAX 4096
# endif

typedef enum e_exit_code
{
	FILE_NOT_EXIST = 126,
	CMD_NOT_FOUND = 127
}	t_exit_code;

typedef struct s_shell
{
	char		**sort_key;
	char		*input;
	char		*path;
	char		*user;
	char		*home;
	char		*oldpwd;
	char		*pwd;
	t_env		*env;
	t_token		*token;
	t_cmds		*cmds;
	int			exit_code;			
}	t_shell;

void	init_shell(t_shell *shell, char **env);
void	increment_shlvl(t_env *env, char *key);
void	execute_cmds(t_shell *shell, char *input);
void	exit_shell(t_shell *shell);

void	free_ptr(void *ptr);
void	free_arg(char **data);

void	*safe_malloc(size_t	size);
char	*safe_strjoin(char *str, char *append);
int		ft_strlen_to_c(char *str, char c);
void	increment_shlvl(t_env *env, char *key);

void	clear_env(t_env *env, char **sort_key);
void	clear_tokens(t_token *token);
void	clear_shell(t_shell *shell);

#endif