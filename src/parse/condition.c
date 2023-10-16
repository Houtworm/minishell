/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   condition.c                                     |o_o || |                */
/*                                                     +:+                    */
/*   By: houtworm <codam@houtworm.net>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/27 19:35:17 by houtworm      #+#    #+#                 */
/*   Updated: 2023/10/16 11:44:15 by houtworm     \___)=(___/                 */
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

t_forks ft_parseendcondition(t_shell *msh, int forknumber)
{
	int		icmd;
	int		ifpip;
	int		icpip;

	msh->frk[forknumber].cmdamount = ft_countendconditions(msh->frk[forknumber].pipeline, 0, 0);
	msh->frk[forknumber].cmd = ft_calloc(10000 * sizeof(t_commands), 1);
	icmd = 0;
	ifpip = 0;
	while (msh->frk[forknumber].pipeline[ifpip] && icmd < msh->frk[forknumber].cmdamount)
	{
		icpip = 0;
		msh->frk[forknumber].cmd[icmd].pipeline = ft_calloc(1000 * 8, 1);
		while (!ft_strchr("&|;\"\'", msh->frk[forknumber].pipeline[ifpip]))
		{
			msh->frk[forknumber].cmd[icmd].pipeline[icpip] = msh->frk[forknumber].pipeline[ifpip];
			ifpip++;
			icpip++;
		}
		if (msh->frk[forknumber].pipeline[ifpip] == '\"' || msh->frk[forknumber].pipeline[ifpip] == '\'')
		{
			ft_copyquote(&(msh->frk[forknumber].cmd[icmd].pipeline), msh->frk[forknumber].pipeline, icpip, ifpip);
			icpip = ft_strlen(msh->frk[forknumber].cmd[icmd].pipeline);
			ifpip = ft_skipquote(msh->frk[forknumber].pipeline, ifpip) + 1;
			if (msh->frk[forknumber].pipeline[ifpip] == '\"' || msh->frk[forknumber].pipeline[ifpip] == '\'')
			{
				ft_copyquote(&(msh->frk[forknumber].cmd[icmd].pipeline), msh->frk[forknumber].pipeline, icpip, ifpip);
				icpip = ft_strlen(msh->frk[forknumber].cmd[icmd].pipeline);
				ifpip = ft_skipquote(msh->frk[forknumber].pipeline, ifpip) + 1;
			}
			while (msh->frk[forknumber].pipeline[ifpip] && !ft_strchr("&|;", msh->frk[forknumber].pipeline[ifpip]))
			{
					msh->frk[forknumber].cmd[icmd].pipeline[icpip] = msh->frk[forknumber].pipeline[ifpip];
					ifpip++;
					icpip++;
			}
		}
		msh->frk[forknumber].cmd[icmd].pipeline[icpip] = '\0';
		if (msh->frk[forknumber].pipeline[ifpip] == '|')
		{
			ifpip++;
			msh->frk[forknumber].cmd[icmd + 1].condition = 2;
		}
		else if (msh->frk[forknumber].pipeline[ifpip] == '&')
		{
			if (msh->frk[forknumber].pipeline[ifpip + 1] == '&')
			{
				ifpip++;
				msh->frk[forknumber].cmd[icmd + 1].condition = 1;
			}
			else
				msh->frk[forknumber].cmd[icmd].detatch++;
		}
		else
			msh->frk[forknumber].cmd[icmd + 1].condition = 0;
		if (msh->frk[forknumber].cmd[icmd + 1].condition && msh->forkamount >forknumber)
			msh->frk[forknumber + 1].waitforlast = 1;
		ifpip++;
		icmd++;
	}
	return (msh->frk[forknumber]);
}
