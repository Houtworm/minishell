/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                         |o_o || |                */
/*                                                    +:+ +:+         +:+     */
/*   By: houtworm <codam@houtworm.net>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 18:13:05 by houtworm          #+#    #+#             */
/*   Updated: 2023/10/02 00:49:52 by houtworm     \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_unset(t_cmds cmds)
{
	int		i;

	i = 0;
	if (cmds.arguments[1][0] == '-')
		if (ft_moderrorexit("invalid option", "unset", cmds.arguments[1], 0))
			return (2);
	while (cmds.envp[i])
	{
		if (!ft_strncmp(cmds.envp[i], cmds.arguments[1], ft_strlen(cmds.arguments[1])))
		{
			cmds.envp[i] = cmds.envp[i + 1];
			while (cmds.envp[i + 1])
			{
				cmds.envp[i] = cmds.envp[i + 1];
				i++;
			}
		}
		i++;
	}
	ft_charpptofd(cmds.envp, cmds.envpfd);
	return (0);
}
