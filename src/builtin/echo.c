/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                          |o_o || |                */
/*                                                    +:+ +:+         +:+     */
/*   By: houtworm <codam@houtworm.net>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 18:13:11 by houtworm          #+#    #+#             */
/*   Updated: 2023/08/26 12:37:32 by djonker      \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_echo(t_cmds cmds)
{
	char	*print;
	int		i;
	int		j;
	int		k;
	char	*line;

	i = 0;
	j = 0;
	k = 0;
	if (cmds.arguments[1])
	{
		print = ft_calloc(512, 1);
		line = cmds.arguments[1];
		if (line[i + j] == '-')
		{
			j++;
			while (line[i + j + k] == 'n')
				k++;
			if (line[i + j + k] == ' ')
				k++;
			else
			{
				k = 0;
				j--;
			}
		}
		while (line[i + j + k] != '\0')
		{
			print[i] = line[j + i + k];
			i++;
		}
		print[i] = '\0';
		ft_printf("%s", print);
		if (k == 0)
			ft_printf("\n");
	}
	else
		ft_printf("\n");
	return (0);
}

int	ft_echo(t_cmds cmds)
{
	char	*print;
	int		i;
	int		j;
	int		k;
	char	*line;

	i = 0;
	j = 0;
	k = 0;
	if (cmds.arguments[1])
	{
		print = ft_calloc(512, 1);
		line = cmds.arguments[1];
		if (line[i + j] == '-')
		{
			j++;
			while (line[i + j + k] == 'n')
				k++;
			if (line[i + j + k] == ' ')
				k++;
			else
			{
				k = 0;
				j--;
			}
		}
		while (line[i + j + k] != '\0')
		{
			print[i] = line[j + i + k];
			i++;
		}
		print[i] = '\0';
		ft_printf("%s", print);
		if (k == 0)
			ft_printf("\n");
	}
	else
		ft_printf("\n");
	return (0);
}
