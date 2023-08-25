/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                          |o_o || |                */
/*                                                    +:+ +:+         +:+     */
/*   By: houtworm <codam@houtworm.net>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 18:13:11 by houtworm          #+#    #+#             */
/*   Updated: 2023/08/25 02:29:20 by houtworm     \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_echo(t_cmds cmds)
{
	char	*line;
	char	*print;
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 5;
	k = 0;
	if (!ft_strncmp(cmds.arguments[0], "echo ", 5))
	{
		print = ft_calloc(512, 1);
		line = cmds.arguments[0];
		if (line[i + j] == '-')
		{
			j++;
			while (line[i + j + k] == 'n')
				k++;
			if (line[i + j + k] == ' ')
				k++;
			/*else if	(line[i + j + k] == '\0')*/
				/*k = k;*/
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
	if (!ft_strncmp(cmds.arguments[0], "echo\0", 5))
		ft_printf("\n");
	return (0);
}
