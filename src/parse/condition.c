/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   condition.c                                     |o_o || |                */
/*                                                     +:+                    */
/*   By: houtworm <codam@houtworm.net>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/27 19:35:17 by houtworm      #+#    #+#                 */
/*   Updated: 2023/10/07 01:39:19 by djonker      \___)=(___/                 */
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
		while (line[i] == ' ')
			i++;
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

t_forks ft_parseendcondition(t_shell *shell, int forknumber)
{
	int		icmd;
	int		ifpip;
	int		icpip;

	shell->forks[forknumber].cmdamount = ft_countendconditions(shell->forks[forknumber].pipeline, 0, 0);
	shell->forks[forknumber].cmds = ft_calloc(10000 * sizeof(t_cmds), 1);
	icmd = 0;
	ifpip = 0;
	while (shell->forks[forknumber].pipeline[ifpip] && icmd < shell->forks[forknumber].cmdamount)
	{
		icpip = 0;
		shell->forks[forknumber].cmds[icmd].pipeline = ft_calloc(1000 * 8, 1);
		while (!ft_strchr("&|;\"\'", shell->forks[forknumber].pipeline[ifpip]))
		{
			shell->forks[forknumber].cmds[icmd].pipeline[icpip] = shell->forks[forknumber].pipeline[ifpip];
			ifpip++;
			icpip++;
		}
		if (shell->forks[forknumber].pipeline[ifpip] == '\"' || shell->forks[forknumber].pipeline[ifpip] == '\'')
		{
			ft_copyquote(&(shell->forks[forknumber].cmds[icmd].pipeline), shell->forks[forknumber].pipeline, icpip, ifpip);
			icpip = ft_strlen(shell->forks[forknumber].cmds[icmd].pipeline);
			ifpip = ft_skipquote(shell->forks[forknumber].pipeline, ifpip) + 1;
			if (shell->forks[forknumber].pipeline[ifpip] == '\"' || shell->forks[forknumber].pipeline[ifpip] == '\'')
			{
				ft_copyquote(&(shell->forks[forknumber].cmds[icmd].pipeline), shell->forks[forknumber].pipeline, icpip, ifpip);
				icpip = ft_strlen(shell->forks[forknumber].cmds[icmd].pipeline);
				ifpip = ft_skipquote(shell->forks[forknumber].pipeline, ifpip) + 1;
			}
			while (shell->forks[forknumber].pipeline[ifpip] && !ft_strchr("&|;", shell->forks[forknumber].pipeline[ifpip]))
			{
					shell->forks[forknumber].cmds[icmd].pipeline[icpip] = shell->forks[forknumber].pipeline[ifpip];
					ifpip++;
					icpip++;
			}
		}
		shell->forks[forknumber].cmds[icmd].pipeline[icpip] = '\0';
		if (shell->forks[forknumber].pipeline[ifpip] == '|')
		{
			ifpip++;
			shell->forks[forknumber].cmds[icmd + 1].condition = 2;
		}
		else if (shell->forks[forknumber].pipeline[ifpip] == '&')
		{
			if (shell->forks[forknumber].pipeline[ifpip + 1] == '&')
			{
				ifpip++;
				shell->forks[forknumber].cmds[icmd + 1].condition = 1;
			}
			else
				shell->forks[forknumber].cmds[icmd].detatch++;
		}
		else
			shell->forks[forknumber].cmds[icmd + 1].condition = 0;
		ifpip++;
		icmd++;
	}
	return (shell->forks[forknumber]);
}
