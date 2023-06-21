/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                        |o_o || |                */
/*                                                    +:+ +:+         +:+     */
/*   By: houtworm <codam@houtworm.net>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 18:12:44 by houtworm          #+#    #+#             */
/*   Updated: 2023/05/29 23:07:54 by houtworm     \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_export(t_shell *strct)
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
	line = strct->line;
	while (line[i + 6] != '\0')
	{
		var[i] = line[7 + i];
		i++;
		if (line[7 + i] == '=')
		{
			i++;
			break ;
		}
	}
	ft_printf("%s\n", var);
	while (line[i + j + 7] != ' ' && line[i + j + 7] != '\0')
	{
		val[j] = line[7 + i + j];
		j++;
	}
	ft_setenv(strct->envp, var, val);
	ft_printf("%s\n", val);
	free(var);
	free(val);
	return (0);
}
