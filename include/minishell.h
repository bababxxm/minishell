/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkhienko42 <pkhienko42@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 18:22:50 by sklaokli          #+#    #+#             */
/*   Updated: 2025/05/13 01:21:37 by pkhienko42       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <fcntl.h>
# include <errno.h>
# include <limits.h>
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
# include "_signal.h"
# include "command.h"

# define B_YELLOW "\001\033[1;33m\002"
# define B_GREEN "\001\033[1;32m\002"
# define B_CYAN "\001\033[1;36m\002"
# define B_RED "\001\033[1;31m\002"
# define YELLOW "\001\033[0;33m\002"
# define GREEN "\001\033[0;32m\002"
# define CYAN "\001\033[0;36m\002"
# define RED "\001\033[0;31m\002"
# define RESET "\001\033[0m\002" 

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
	pid_t		pid;
	int			exit_code;			
}	t_shell;

void	init_shell(t_shell *shell, char **env);
void	increment_shlvl(t_env *env, char *key);
void	execute_cmds(t_shell *shell);
void	exit_shell(t_shell *shell);
void	sighandler(int signum);

void	*safe_malloc(size_t	size);
char    *get_prompt(t_shell *shell);
char	*strappend(char *str, char *append);
int		ft_strlen_to_c(char *str, char c);
void	increment_shlvl(t_env *env, char *key);

void	clear_shell();

#endif