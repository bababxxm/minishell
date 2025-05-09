/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkhienko42 <pkhienko42@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 18:22:50 by sklaokli          #+#    #+#             */
/*   Updated: 2025/05/09 04:52:00 by pkhienko42       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <fcntl.h>
# include <errno.h>
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include <string.h>
# include <stdbool.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <readline/history.h>
# include <readline/readline.h>

# include "libft.h"
# include "env.h"
# include "lexer.h"
# include "builtin.h"
# include "command.h"

# define B_YELLOW "\033[1;33m"
# define B_GREEN "\033[1;32m"
# define B_CYAN "\033[1;36m"
# define B_RED "\033[1;31m"
# define YELLOW "\033[0;33m"
# define GREEN "\033[0;32m"
# define CYAN "\033[0;36m"
# define RED "\033[0;31m"
# define RESET "\033[0m"

# define PROMPT B_RED"Minishell "

# ifndef PATH_MAX
#  define PATH_MAX 4096
# endif

typedef enum e_exit_code
{
	CMD_NOT_EXECUTABLE = 126,
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
void	execute_cmds(t_shell *shell);
void	exit_shell(t_shell *shell);
void	sighandler(int signum);

void	*safe_malloc(size_t	size);
char	*strappend(char *str, char *append);
int		ft_strlen_to_c(char *str, char c);
void	increment_shlvl(t_env *env, char *key);

void	clear_shell();

#endif