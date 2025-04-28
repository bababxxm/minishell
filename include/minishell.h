/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklaokli <sklaokli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 18:22:50 by sklaokli          #+#    #+#             */
/*   Updated: 2025/04/19 22:45:59 by sklaokli         ###   ########.fr       */
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
# include "token.h"
# include "command.h"

# define B_YELLOW "\033[1;33m"
# define B_GREEN "\033[1;32m"
# define B_CYAN "\033[1;36m"
# define B_RED "\033[0;31m"
# define YELLOW "\033[0;33m"
# define GREEN "\033[0;32m"
# define CYAN "\033[0;36m"
# define RED "\033[0;31m"
# define RESET "\033[0m"

# define PROMPT GREEN" ➜ "RESET

# ifndef PATH_MAX
#  define PATH_MAX 4096
# endif

typedef struct s_env
{
	struct s_env	*next;
	char			*key;
	char			equal;
	char			*value;
}	t_env;

typedef struct s_shell
{
	char			**sort_key;
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

// main
void    init_shell(t_shell *shell, char **env);
void    execute_cmds(t_shell *shell, char *input);
char    *parser(t_shell *shell, char *input);

// builtins
int		ft_env(t_env *env);
int		ft_echo(char **av);
int		ft_pwd(t_shell *shell);
int		ft_unset(t_env **env, char **av);
int		ft_cd(t_shell *shell, char **av);
int		ft_exit(t_shell *shell, char **av);
int		ft_export(t_shell *shell, char **av);

// memory
void	free_ptr(void *ptr);
void	free_arg(char **data);

// utils
void	print_export(t_shell *shell);
void	*safe_malloc(size_t	size);
void	set_bool(bool *data, bool op);
char	*safe_strjoin(char *str, char *append);
char	*handle_key(char *str, bool equal_and_plus[]);
char	**update_list_key(t_env *env);
int		ft_strlen_to_c(char *str, char c);

// env
void	clear_env(t_shell *shell);
void	del_env(t_env **env, char *key);
void	set_env(t_env **env, char *key, char *value);
char	*dup_var(char *str, char c);
t_env	*dup_env(char **env);
t_env	*search_env(t_env *env, char *key);
t_env	*new_env(char *key, char equal, char *value);

//error_msg
int	errmsg_cmd(char *cmd, char *detail, char *err_msg, int err_nb);

// token
t_token	*get_tokens(char *input);

// debug
void	print_env(t_env *env);

#endif