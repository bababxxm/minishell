/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklaokli <sklaokli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 18:22:50 by sklaokli          #+#    #+#             */
/*   Updated: 2025/04/09 02:17:56 by sklaokli         ###   ########.fr       */
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

# define CYAN "\033[0;36m"
# define RESET "\033[0m"

# define PROMPT "minishell"

typedef enum e_shell_status
{
	SH_FAILURE,
	SH_INTERRUPTED,
	SH_SUCCESS
}	t_shell_status;

typedef struct s_env
{
	char			*key;
	char			equal;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_shell
{
	char			*input;
	char			*line;
	t_env			*env;
	t_tree			*cmds;
}	t_shell;

int		ft_strlen(char *str);
int		ft_strlen_to_c(char *str, char c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strdup(char *src);
t_env	*new_env(char *key, char equal, char *value);
t_env	*last_env(t_env *env);
void	env_addback(t_env **env, t_env *new);
char	*dup_var(char *str, char c);
t_env	*dup_env(char *env[]);
char	*search_env(char *key, t_env *env);
void	clear_env(t_env *env);

#endif