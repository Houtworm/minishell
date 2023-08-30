/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   condition.c                                     |o_o || |                */
/*                                                     +:+                    */
/*   By: houtworm <codam@houtworm.net>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/27 19:35:17 by houtworm      #+#    #+#                 */
/*   Updated: 2023/08/30 03:25:35 by djonker      \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int		ft_countendconditions(char *line, int count, int i)
{
	while (line[i])
	{
		while (!ft_strchr("&|;\'\"", line[i]))
			i++;
		if (line[i] == '\'' || line[i] == '\"')
			i = ft_skipquote(line, i) + 1;
		count++;
		if (line[i] == '&')
		{
			i++;
			if (line[i] == '&')
				i++;
		}
		if (line[i] == '|')
		{
			i++;
			if (line[i] == '|')
				i++;
		}
		if (line[i] == ';')
		{
			i++;
		}
	}
	return (count);
}

t_forks ft_parseendcondition(t_forks forks)
{
	int		icmd;
	int		ifpip;
	int		icpip;
	int		tmp;

	forks.cmdamount = ft_countendconditions(forks.pipeline, 0, 0);
	forks.cmds = ft_calloc(10000 * sizeof(t_cmds), 1);
	icmd = 0;
	ifpip = 0;
	while (forks.pipeline[ifpip])
	{
		icpip = 0;
		forks.cmds[icmd].pipeline = ft_calloc(1000 * 8, 1);
		while (!ft_strchr("&|;\"\'", forks.pipeline[ifpip]))
		{
			forks.cmds[icmd].pipeline[icpip] = forks.pipeline[ifpip];
			ifpip++;
			icpip++;
		}
		if (forks.pipeline[ifpip] == '\"' || forks.pipeline[ifpip] == '\'')
		{
			forks.cmds[icmd].pipeline[icpip] = forks.pipeline[ifpip];
			tmp = ifpip;
			ifpip++;
			icpip++;
			while (forks.pipeline[tmp] != forks.pipeline[ifpip])
			{
				forks.cmds[icmd].pipeline[icpip] = forks.pipeline[ifpip];
				ifpip++;
				icpip++;
			}
			forks.cmds[icmd].pipeline[icpip] = forks.pipeline[ifpip];
			ifpip++;
			icpip++;
		}
		forks.cmds[icmd].pipeline[icpip] = '\0';
		if (forks.pipeline[ifpip] == '|')
		{
			ifpip = ifpip + 2;
			forks.cmds[icmd + 1].condition = 2;
		}
		else if (forks.pipeline[ifpip] == '&')
		{
			ifpip++;
			if (forks.pipeline[ifpip] == '&')
			{
				ifpip++;
				forks.cmds[icmd + 1].condition = 1;
			}
			else
				forks.cmds[icmd].detatch = 1;
		}
		else
		{
			ifpip++;
			forks.cmds[icmd + 1].condition = 0;
		}
		icmd++;
	}
	return (forks);
}
