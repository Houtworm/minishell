/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                         |o_o || |                */
/*                                                    +:+ +:+         +:+     */
/*   By: houtworm <codam@houtworm.net>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 18:13:05 by houtworm          #+#    #+#             */
/*   Updated: 2023/10/16 10:48:00 by houtworm     \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_unset(t_commands cmd, t_shell *shell)
{
	int		i;

	i = 0;
	if (cmd.arg[1] && cmd.arg[1][0] == '-')
		return (ft_errorret2("invalid option", "unset", cmd.arg[1], 2));
	while (shell->envp[i])
	{
		if (!ft_strncmp(shell->envp[i], cmd.arg[1], ft_strlen(cmd.arg[1])))
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
