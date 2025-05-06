/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklaokli <sklaokli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 18:42:35 by sklaokli          #+#    #+#             */
/*   Updated: 2025/05/07 01:21:06 by sklaokli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

typedef struct s_shell	t_shell;

typedef struct s_env
{
	struct s_env	*next;
	char			*key;
	char			equal;
	char			*value;
}	t_env;

char	*dup_var(char *str, char c);
t_env	*dup_env(char **env);
t_env	*new_env(char *key, char equal, char *value);
void	set_env(t_env **env, char *key, char *value);
t_env	*search_env(t_env *env, char *key);
char	*get_value(t_env *env, char *key);
void	del_env(t_env **env, char *key);
void	del_env_util(t_env *cur);
void	clear_env(t_env *env, char **sort_key);

#endif