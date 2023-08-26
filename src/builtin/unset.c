/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                         |o_o || |                */
/*                                                    +:+ +:+         +:+     */
/*   By: houtworm <codam@houtworm.net>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 18:13:05 by houtworm          #+#    #+#             */
/*   Updated: 2023/08/26 05:38:09 by djonker      \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_unset(t_cmds cmds)
{
	char	*line;
	char	*var;
	int		i;

	i = 0;
	var = ft_calloc(512, 1);
	line = cmds.arguments[1];
	while (line[i + 6] != ' ' && line[i + 5] != '\0')
	{
		var[i] = line[5 + i];
		i++;
	}
	while (cmds.envp[i])
	{
		if (!ft_strncmp(cmds.envp[i], var, ft_strlen(var)))
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
	return (0);
}
