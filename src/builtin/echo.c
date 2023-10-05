/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                          |o_o || |                */
/*                                                    +:+ +:+         +:+     */
/*   By: houtworm <codam@houtworm.net>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 18:13:11 by houtworm          #+#    #+#             */
/*   Updated: 2023/10/05 09:51:10 by houtworm     \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int ft_echorecursion(t_cmds cmds, char *print, int i, int j)
{
	int k;

	k = 0;
	if (!cmds.arguments[j])
		return (0);
	/*if (cmds.arguments[j][k] == '~')*/
		/*cmds.arguments[j] = ft_strjoin(ft_gethome(cmds.envp), &cmds.arguments[j][1]);*/
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


int	ft_echo(t_cmds cmds, t_shell *shell)
{
	char	*print;
	int		i;
	int		j;
	int		l;
	int		flag;

	i = 0;
	j = 1;
	l = 0;
	flag = 0;
	if (cmds.arguments[1])
	{
		print = ft_calloc(1000, 8);
		if (cmds.arguments[j][0] == '-')
		{
			l++;
			while (cmds.arguments[j][l] == 'n')
				l++;
			if (cmds.arguments[j][l] == '\0')
			{
				i = i + l;
				flag = 1;
				j++;
				while (cmds.arguments[j] && cmds.arguments[j][0] == '-')
				{
					l = 1;
					while (cmds.arguments[j] && cmds.arguments[j][l] == 'n')
						l++;
					if (cmds.arguments[j][l] == '\0')
						i = i + l;
					else
						break ;
					j++;
				}
			}
		}
		ft_echorecursion(cmds, print, 0, j);
		if (flag == 0)
			ft_putendl(print);
		else
			ft_putstr(print);
		free(print);
	}
	else
		ft_putchar('\n');
	return (0);
	shell = shell;
}
