/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                           |o_o || |                */
/*                                                    +:+ +:+         +:+     */
/*   By: houtworm <codam@houtworm.net>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 18:13:00 by houtworm          #+#    #+#             */
/*   Updated: 2023/09/30 03:08:16 by houtworm     \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_pwd(t_cmds cmds)
{
	/*if (cmds.arguments[5]) // Why is this 5? split_not_quote?*/
		/*if (ft_errorexit("ignoring non-option arguments", "pwd", 0)) // still goes here if cd arg is followed by a space*/
	printf("%s\n", ft_getpwd(cmds.envp, 0));
	return (0);
}
