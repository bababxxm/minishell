/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklaokli <sklaokli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 18:22:50 by sklaokli          #+#    #+#             */
/*   Updated: 2025/04/09 00:01:53 by sklaokli         ###   ########.fr       */
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

# define CYAN "\033[0;36m"
# define RESET "\033[0m"

# define PROMPT "minishell"

typedef enum e_status
{
	ERROR,
	EXIT,
	SUCCESS
}	t_status;

typedef struct s_tree
{
	char			*cmd;
	struct s_tree	*left;
	struct s_tree	*right;
}	t_tree;

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
	t_tree			*token;
}	t_shell;

#endif