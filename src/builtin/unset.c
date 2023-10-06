/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                         |o_o || |                */
/*                                                    +:+ +:+         +:+     */
/*   By: houtworm <codam@houtworm.net>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 18:13:05 by houtworm          #+#    #+#             */
/*   Updated: 2023/10/06 17:07:38 by houtworm     \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_unset(t_cmds cmds, t_shell *shell)
{
	int		i;

	i = 0;
	if (cmds.arguments[1][0] == '-')
		if (ft_moderrorexit("invalid option", "unset", cmds.arguments[1], 0))
			return (2);
	while (shell->envp[i])
	{
		if (!ft_strncmp(shell->envp[i], cmds.arguments[1], ft_strlen(cmds.arguments[1])))
		{
			free(shell->envp[i]);
			shell->envp[i] = ft_strdup(shell->envp[i + 1]);
			while (shell->envp[i + 1])
			{
				free(shell->envp[i]);
				shell->envp[i] = ft_strdup(shell->envp[i + 1]);
				i++;
			}
		}
		i++;
	}
	ft_charpptofd(shell->envp, shell->envpfd);
	return (0);
}
