/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   condition.c                                     |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: houtworm <codam@houtworm.net>              //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/08/27 19:35:17 by houtworm     /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/08/27 22:38:10 by houtworm     \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int		ft_countendconditions(char *line, int count, int i)
{
	while (line[i])
	{
		if (line[i] == '&')
		{
			i++;
			count++;
			if (line[i + 1] == '&')
				i++;
		}
		if (line[i] == '|')
		{
			i++;
			count++;
			if (line[i + 1] == '|')
				i++;
		}
		if (line[i] == ';')
		{
			i++;
			count++;
		}
		i++;
	}
	return (count);
}

t_forks ft_parseendcondition(t_forks forks)
{
	int		icmd;
	int		ifpip;
	int		icpip;
	
	forks.cmdamount = ft_countendconditions(forks.pipeline, 0, 0) + 1;
	forks.cmds = ft_calloc(10000 * sizeof(t_cmds), 1);
	icmd = 0;
	ifpip = 0;
	icpip = 0;
	while (forks.pipeline[ifpip])
	{
		forks.cmds[icmd].pipeline = ft_calloc(1000 * 8, 1);
		while (!ft_strchr("&|;", forks.pipeline[ifpip]))
		{
			forks.cmds[icmd].pipeline[icpip] = forks.pipeline[ifpip];
			ifpip++;
			icpip++;
		}
		forks.cmds[icmd].pipeline[icpip] = '\0';
		if (!forks.pipeline[ifpip])
			return (forks);
		if (forks.pipeline[ifpip] == '|')
		{
			ifpip = ifpip + 2;
			forks.cmds[icmd + 1].condition = 2;
		}
		if (!forks.pipeline[ifpip])
			return (forks);
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
		if (!forks.pipeline[ifpip])
			return (forks);
		else
		{
			ifpip++;
			forks.cmds[icmd + 1].condition = 0;
		}
		icmd++;
	}
	return (forks);
}
