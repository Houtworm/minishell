/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                          |o_o || |                */
/*                                                    +:+ +:+         +:+     */
/*   By: houtworm <codam@houtworm.net>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 18:13:11 by houtworm          #+#    #+#             */
/*   Updated: 2023/10/16 10:35:28 by houtworm     \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int ft_echorecursion(t_commands cmd, char *print, int i, int j)
{
	int k;

	k = 0;
	if (!cmd.arg[j])
		return (0);
	while (cmd.arg[j][k] != '\0')
	{
		print[i] = cmd.arg[j][k];
		i++;
		k++;
	}
	if (cmd.arg[j + 1])
	{
		print[i] = ' ';
		ft_echorecursion(cmd, print, i + 1, j + 1);
	}
	else
		print[i] = '\0';
	return (j);
}


int	ft_echo(t_commands cmd, t_shell *shell)
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
	if (cmd.arg[1])
	{
		print = ft_calloc(1000, 8);
		if (cmd.arg[j][0] == '-')
		{
			l++;
			while (cmd.arg[j][l] == 'n')
				l++;
			if (cmd.arg[j][l] == '\0')
			{
				i = i + l;
				flag = 1;
				j++;
				while (cmd.arg[j] && cmd.arg[j][0] == '-')
				{
					l = 1;
					while (cmd.arg[j] && cmd.arg[j][l] == 'n')
						l++;
					if (cmd.arg[j][l] == '\0')
						i = i + l;
					else
						break ;
					j++;
				}
			}
		}
		ft_echorecursion(cmd, print, 0, j);
		if (flag == 0)
			printf("%s\n", print);
		else
			printf("%s", print);
		free(print);
	}
	else
		printf("\n");
	return (0);
	shell = shell;
}
