/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklaokli <sklaokli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 18:22:50 by sklaokli          #+#    #+#             */
/*   Updated: 2025/05/14 18:41:44 by sklaokli         ###   ########.fr       */
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

# ifndef ARGV_MAX
#  define ARGV_MAX 1024
# endif

extern volatile sig_atomic_t	g_childern_code;
typedef	struct sigaction		t_sa;

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
	t_sa		sigint;
	t_sa		sigquit;
	t_env		*env;
	t_token		*token;
	t_cmds		*cmds;
	pid_t		pid;
	int			exit_code;			
}	t_shell;

void	sighandler(int sig);
void	exit_shell(t_shell *shell);
void	execute_cmds(t_shell *shell);
void	increment_shlvl(t_env *env, char *key);
void	init_shell(t_shell *shell, char **env);
void	exit_error(t_shell *shell, int err_nb);
void	increment_shlvl(t_env *env, char *key);

char    *get_prompt(t_shell *shell);
char	*strappend(char *str, char *append);

int		ft_strlen_to_c(char *str, char c);

void	set_sigint(t_sa *sigint, void *handler);
void	set_sigquit(t_sa *sigquit, void *handler);

#endif