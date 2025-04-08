/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklaokli <sklaokli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 18:22:50 by sklaokli          #+#    #+#             */
/*   Updated: 2025/04/08 19:15:28 by sklaokli         ###   ########.fr       */
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

# define PROMPT "hellscript"

typedef enum e_status
{
	ERROR,
	EXIT,
	SUCCESS
}	t_status;

typedef struct s_shell
{
	char			*input;
	char			*line;
	struct sigacton	sa;
}	t_shell;

typedef struct s_data
{
	char			*data;
	struct s_data	*left;
	struct s_data	*right;
}	t_data;


#endif