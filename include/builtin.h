/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkhienko42 <pkhienko42@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 01:26:27 by sklaokli          #+#    #+#             */
/*   Updated: 2025/05/13 23:21:02 by pkhienko42       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

void	print_export(t_shell *shell);
void	set_bool(bool *data, bool op);

char	**update_list_key(t_env *env);
char	*handle_key(char *str, bool equal_and_plus[]);

int		ft_env(t_env *env);
int		ft_echo(char **av);
int		ft_pwd(t_shell *shell);
int		ft_cd(t_shell *shell, char **av);
int		ft_exit(t_shell *shell, char **av);
int		ft_unset(t_shell *shell, char **av);
int		ft_export(t_shell *shell, char **av);
int		errmsg(char *cmd, char *detail, char *err_msg, int err_nb);

#endif