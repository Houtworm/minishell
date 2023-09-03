/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                          |o_o || |                */
/*                                                    +:+ +:+         +:+     */
/*   By: houtworm <codam@houtworm.net>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 18:13:11 by houtworm          #+#    #+#             */
/*   Updated: 2023/09/03 22:26:01 by houtworm     \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int ft_echorecursion(t_cmds cmds, char *print, int i, int j)
{
	int k;

	k = 0;
	if (!cmds.arguments[j])
		return (0);
	while (cmds.arguments[j][k] != '\0')
	{
		print[i] = cmds.arguments[j][k];
		i++;
		k++;
	}
	if (cmds.arguments[j + 1])
	{
		print[i] = ' ';
		ft_echorecursion(cmds, print, i + 1, j + 1);
	}
	else
		print[i] = '\0';
	return (j);
}


int	ft_echo(t_cmds cmds)
{
	char	*print;
	int		i;
	int		j;
	int		flag;

	i = 0;
	j = 1;
	flag = 0;
	if (cmds.arguments[1])
	{
		print = ft_calloc(512, 1);
		if (cmds.arguments[1][0] == '-')
		{
			i++;
			while (cmds.arguments[1][i] == 'n')
				i++;
			if (cmds.arguments[1][i] == '\0')
			{
				flag = 1;
				ft_echorecursion(cmds, print, 0, 2);
			}
			else
			{
				i = 0;
				j = ft_echorecursion(cmds, print, i, j);
			}
		}
		else
			ft_echorecursion(cmds, print, i, j);
		if (flag == 0)
			ft_putendl(print);
		else
			ft_putstr(print);
	}
	else
		ft_putchar('\n');
	return (0);
}
