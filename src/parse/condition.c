/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   condition.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: houtworm <codam@houtworm.net>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/27 19:35:17 by houtworm      #+#    #+#                 */
/*   Updated: 2023/09/05 08:54:35 by yitoh         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int		ft_countendconditions(char *line, int count, int i)
{
	while (line[i])
	{
		while (!ft_strchr("&|;\'\"", line[i]))
			i++;
		while (line[i] == '\'' || line[i] == '\"')
		{
			i = ft_skipquote(line, i) + 1;
			while (line[i] == ' ')
				i++;
			while (!ft_strchr("&|;\'\"", line[i]))
				i++;
		}
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

void	ft_copyquote(char **cmdline, char	*forkline, int icpip, int ifpip)
{
	int		check;

	(*cmdline)[icpip] = forkline[ifpip];
	check = ifpip;
	ifpip++;
	icpip++;
	while (forkline[check] != forkline[ifpip])
	{
		(*cmdline)[icpip] = forkline[ifpip];
		ifpip++;
		icpip++;
	}
	(*cmdline)[icpip] = forkline[ifpip];
}

t_forks ft_parseendcondition(t_forks forks)
{
	int		icmd;
	int		ifpip;
	int		icpip;

	forks.cmdamount = ft_countendconditions(forks.pipeline, 0, 0);
	forks.cmds = ft_calloc(10000 * sizeof(t_cmds), 1);
	icmd = 0;
	ifpip = 0;
	while (forks.pipeline[ifpip] && icmd < forks.cmdamount)
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
			ft_copyquote(&(forks.cmds[icmd].pipeline), forks.pipeline, icpip, ifpip);
			icpip = ft_strlen(forks.cmds[icmd].pipeline);
			ifpip = ft_skipquote(forks.pipeline, ifpip) + 1;
			if (forks.pipeline[ifpip] == '\"' || forks.pipeline[ifpip] == '\'')
			{
				ft_copyquote(&(forks.cmds[icmd].pipeline), forks.pipeline, icpip, ifpip);
				icpip = ft_strlen(forks.cmds[icmd].pipeline);
				ifpip = ft_skipquote(forks.pipeline, ifpip) + 1;
			}
			if (forks.pipeline[ifpip] && !ft_strchr("&|", forks.pipeline[ifpip]))
			{
				while ((ft_strnstr(forks.cmds[icmd].pipeline, "echo", 4) && forks.pipeline[ifpip] == ' ')
					|| (forks.pipeline[ifpip] && !ft_strchr("&|; ", forks.pipeline[ifpip])))
				{
					forks.cmds[icmd].pipeline[icpip] = forks.pipeline[ifpip];
					ifpip++;
					icpip++;
				}
			}
		}
		forks.cmds[icmd].pipeline[icpip] = '\0';
		if (forks.pipeline[ifpip] == '|')
		{
			ifpip++;
			forks.cmds[icmd + 1].condition = 2;
		}
		else if (forks.pipeline[ifpip] == '&')
		{
			if (forks.pipeline[ifpip + 1] == '&')
			{
				ifpip++;
				forks.cmds[icmd + 1].condition = 1;
			}
			else
				forks.cmds[icmd].detatch++;
		}
		else
			forks.cmds[icmd + 1].condition = 0;
		ifpip++;
		icmd++;
	}
	return (forks);
}
