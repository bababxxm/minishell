/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklaokli <sklaokli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 00:53:34 by sklaokli          #+#    #+#             */
/*   Updated: 2025/05/07 00:53:36 by sklaokli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(t_shell *shell)
{
	if (shell->pwd)
	{
		printf("%s\n", shell->pwd);
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}
