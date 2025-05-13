/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _signal.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkhienko42 <pkhienko42@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 16:09:14 by sklaokli          #+#    #+#             */
/*   Updated: 2025/05/13 17:38:43 by pkhienko42       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _SIGNAL_H
# define _SIGNAL_H

void	sigchild(int sig);
void	sighandler(int sig);
void	heredoc_sig_handler(int sig);

#endif