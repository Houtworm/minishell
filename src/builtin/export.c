/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                        |o_o || |                */
/*                                                    +:+ +:+         +:+     */
/*   By: houtworm <codam@houtworm.net>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 18:12:44 by houtworm          #+#    #+#             */
/*   Updated: 2023/08/26 05:39:08 by djonker      \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_export(t_cmds cmds)
{
	char	*line;
	char	*var;
	char	*val;
	int		i;
	int		j;

	i = 0;
	j = 0;
	var = ft_calloc(512, 1);
	val = ft_calloc(512, 1);
	line = cmds.arguments[1];
	while (line[i + 7] != '\0' && line[i + 7] != '=')
	{
		var[i] = line[7 + i];
		i++;
	}
	if (line[i + 7] != '=')
		return (1);
	while (line[i + j + 8] != '\0')
	{
		val[j] = line[8 + j + i];
		j++;
	}
	ft_setenv(cmds.envp, var, val);
	free(var);
	free(val);
	return (0);
}
