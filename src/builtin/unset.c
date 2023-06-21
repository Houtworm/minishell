/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                         |o_o || |                */
/*                                                    +:+ +:+         +:+     */
/*   By: houtworm <codam@houtworm.net>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 18:13:05 by houtworm          #+#    #+#             */
/*   Updated: 2023/05/24 05:06:38 by djonker      \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_unset(t_shell *strct)
{
	char	*line;
	char	*var;
	int		i;

	i = 0;
	var = ft_calloc(512, 1);
	line = strct->line;
	while (line[i + 6] != ' ' && line[i + 5] != '\0')
	{
		var[i] = line[5 + i];
		i++;
	}
	while (strct->envp[i])
	{
		if (!ft_strncmp(strct->envp[i], var, ft_strlen(var)))
		{
			strct->envp[i] = strct->envp[i + 1];
			while (strct->envp[i + 1])
			{
				strct->envp[i] = strct->envp[i + 1];
				i++;
			}
		}
		i++;
	}
	return (0);
}
