/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                          |o_o || |                */
/*                                                    +:+ +:+         +:+     */
/*   By: houtworm <codam@houtworm.net>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 18:13:11 by houtworm          #+#    #+#             */
/*   Updated: 2023/08/26 13:10:00 by djonker      \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*int	ft_echo(t_cmds cmds)*/
/*{*/
	/*char	*print;*/
	/*int		i;*/
	/*int		j;*/
	/*int		flag;*/

	/*i = 0;*/
	/*j = 0;*/
	/*flag = 0;*/
	/*if (cmds.arguments[1])*/
	/*{*/
		/*print = ft_calloc(512, 1);*/
		/*if (cmds.arguments[1][0] == '-')*/
		/*{*/
			/*i++;*/
			/*while (cmds.arguments[1][i] == 'n')*/
				/*i++;*/
			/*if (cmds.arguments[1][i] == '\0')*/
				/*flag = 1;*/
			/*else*/
			/*{*/
				/*i = 0;*/
				/*while (cmds.arguments[1][i] != '\0')*/
				/*{*/
					/*print[i] = cmds.arguments[1][i];*/
					/*i++;*/
				/*}*/
				/*print[i] = '\0';*/
			/*}*/
		/*}*/
		/*ft_printf("%s", print);*/
		/*if (flag == 0)*/
			/*ft_printf("\n");*/
	/*}*/
	/*else*/
		/*ft_printf("\n");*/
	/*return (0);*/
/*}*/

int ft_echorecursion(char *print, int i, int j)
{
	int k;

	k = 0;
	while (cmds.arguments[j][k] != '\0')
	{
		print[i] = cmds.arguments[j][k];
		i++;
		k++;
	}
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
				flag = 1;
			else
			{
				i = 0;
				j = ft_echorecursion(print, j + 1);
				print[i] = '\0';
			}
		}
		ft_printf("%s", print);
		if (flag == 0)
			ft_printf("\n");
	}
	else
		ft_printf("\n");
	return (0);
}

// make it recursive damnit
