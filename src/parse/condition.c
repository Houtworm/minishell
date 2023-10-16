/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   condition.c                                     |o_o || |                */
/*                                                     +:+                    */
/*   By: houtworm <codam@houtworm.net>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/27 19:35:17 by houtworm      #+#    #+#                 */
/*   Updated: 2023/10/16 10:28:06 by houtworm     \___)=(___/                 */
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

	shell->frk[forknumber].cmdamount = ft_countendconditions(shell->frk[forknumber].pipeline, 0, 0);
	shell->frk[forknumber].cmd = ft_calloc(10000 * sizeof(t_commands), 1);
	icmd = 0;
	ifpip = 0;
	while (shell->frk[forknumber].pipeline[ifpip] && icmd < shell->frk[forknumber].cmdamount)
	{
		icpip = 0;
		shell->frk[forknumber].cmd[icmd].pipeline = ft_calloc(1000 * 8, 1);
		while (!ft_strchr("&|;\"\'", shell->frk[forknumber].pipeline[ifpip]))
		{
			shell->frk[forknumber].cmd[icmd].pipeline[icpip] = shell->frk[forknumber].pipeline[ifpip];
			ifpip++;
			icpip++;
		}
		if (shell->frk[forknumber].pipeline[ifpip] == '\"' || shell->frk[forknumber].pipeline[ifpip] == '\'')
		{
			ft_copyquote(&(shell->frk[forknumber].cmd[icmd].pipeline), shell->frk[forknumber].pipeline, icpip, ifpip);
			icpip = ft_strlen(shell->frk[forknumber].cmd[icmd].pipeline);
			ifpip = ft_skipquote(shell->frk[forknumber].pipeline, ifpip) + 1;
			if (shell->frk[forknumber].pipeline[ifpip] == '\"' || shell->frk[forknumber].pipeline[ifpip] == '\'')
			{
				ft_copyquote(&(shell->frk[forknumber].cmd[icmd].pipeline), shell->frk[forknumber].pipeline, icpip, ifpip);
				icpip = ft_strlen(shell->frk[forknumber].cmd[icmd].pipeline);
				ifpip = ft_skipquote(shell->frk[forknumber].pipeline, ifpip) + 1;
			}
			while (shell->frk[forknumber].pipeline[ifpip] && !ft_strchr("&|;", shell->frk[forknumber].pipeline[ifpip]))
			{
					shell->frk[forknumber].cmd[icmd].pipeline[icpip] = shell->frk[forknumber].pipeline[ifpip];
					ifpip++;
					icpip++;
			}
		}
		shell->frk[forknumber].cmd[icmd].pipeline[icpip] = '\0';
		if (shell->frk[forknumber].pipeline[ifpip] == '|')
		{
			ifpip++;
			shell->frk[forknumber].cmd[icmd + 1].condition = 2;
		}
		else if (shell->frk[forknumber].pipeline[ifpip] == '&')
		{
			if (shell->frk[forknumber].pipeline[ifpip + 1] == '&')
			{
				ifpip++;
				shell->frk[forknumber].cmd[icmd + 1].condition = 1;
			}
			else
				shell->frk[forknumber].cmd[icmd].detatch++;
		}
		else
			shell->frk[forknumber].cmd[icmd + 1].condition = 0;
		if (shell->frk[forknumber].cmd[icmd + 1].condition && shell->forkamount >forknumber)
			shell->frk[forknumber + 1].waitforlast = 1;
		ifpip++;
		icmd++;
	}
	return (shell->frk[forknumber]);
}
