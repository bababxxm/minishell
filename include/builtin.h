/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklaokli <sklaokli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 01:26:27 by sklaokli          #+#    #+#             */
/*   Updated: 2025/05/07 01:26:34 by sklaokli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

int		ft_env(t_env *env);
int		ft_echo(char **av);
int		ft_pwd(t_shell *shell);
int		ft_unset(t_shell *shell, char **av);
int		ft_cd(t_shell *shell, char **av);
int		ft_exit(t_shell *shell, char **av);
int		ft_export(t_shell *shell, char **av);

void	set_bool(bool *data, bool op);
void	print_export(t_shell *shell);
char	*handle_key(char *str, bool equal_and_plus[]);
char	**update_list_key(t_env *env);
int		errmsg_cmd(char *cmd, char *detail, char *err_msg, int err_nb);

#endif