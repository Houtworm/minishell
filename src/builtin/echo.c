/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: houtworm <codam@houtworm.net>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/21 18:13:11 by houtworm      #+#    #+#                 */
/*   Updated: 2023/10/19 02:08:41 by djonker       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_echorecursion(t_commands cmd, char *print, int i, int j)
{
	int	k;

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

int	*ft_echooption(t_commands cmd, int *flagcount)
{
	int	i;

	i = 1;
	while (cmd.arg[flagcount[2]][i] == 'n')
		i++;
	if (cmd.arg[flagcount[2]][i] == '\0')
	{
		flagcount[1] += i;
		flagcount[0] = 1;
		flagcount[2]++;
		while (cmd.arg[flagcount[2]] && cmd.arg[flagcount[2]][0] == '-')
		{
			i = 1;
			while (cmd.arg[flagcount[2]] && cmd.arg[flagcount[2]][i] == 'n')
				i++;
			if (cmd.arg[flagcount[2]][i] == '\0')
				flagcount[1] += i;
			else
				break ;
			flagcount[2]++;
		}
	}
	return (flagcount);
}

int	ft_echo(t_commands cmd, t_shell *msh)
{
	char	*print;
	int		*flagcount;

	flagcount = ft_calloc(4, 32);
	flagcount[0] = 0;
	flagcount[1] = 0;
	flagcount[2] = 1;
	if (cmd.arg[1])
	{
		print = ft_calloc(10000, 8);
		if (cmd.arg[1][0] == '-')
			ft_echooption(cmd, flagcount);
		ft_echorecursion(cmd, print, 0, flagcount[2]);
		if (flagcount[0] == 0)
			printf("%s\n", print);
		else
			printf("%s", print);
		free(print);
	}
	else
		printf("\n");
	msh = msh;
	free(flagcount);
	return (0);
}
