/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   condition.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: houtworm <codam@houtworm.net>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/27 19:35:17 by houtworm      #+#    #+#                 */
/*   Updated: 2023/10/20 16:15:53 by houtworm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_countendconditions(char *line, int count, int i)
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
		if (line[i] == '&' || line[i] == '|' || line[i] == ';')
		{
			i++;
			if (line[i] == line[i - 1] && line[i] != ';')
				i++;
		}
		while (line[i] == ' ')
			i++;
	}
	return (count);
}

int	ft_cpquote(char **cmdline, char *forkline, int *icpip, int ifpip)
{
	int		check;

	(*cmdline)[*icpip] = forkline[ifpip];
	check = ifpip;
	ifpip++;
	(*icpip)++;
	while (forkline[check] != forkline[ifpip])
	{
		(*cmdline)[*icpip] = forkline[ifpip];
		ifpip++;
		(*icpip)++;
	}
	(*cmdline)[*icpip] = forkline[ifpip];
	(*icpip)++;
	return (ifpip + 1);
}

int	ft_foundcondition(t_shell *msh, int n, int a, int ifpip)
{
	if (msh->frk[n].line[ifpip] == '|')
	{
		ifpip++;
		msh->frk[n].cmd[a + 1].condition = 2;
	}
	else if (msh->frk[n].line[ifpip] == '&')
	{
		if (msh->frk[n].line[ifpip + 1] == '&')
		{
			ifpip++;
			msh->frk[n].cmd[a + 1].condition = 1;
		}
	}
	else
		msh->frk[n].cmd[a + 1].condition = 0;
	if (msh->frk[n].cmd[a + 1].condition && msh->forks > n)
		msh->frk[n + 1].waitforlast = 1;
	ifpip++;
	return (ifpip);
}

t_forks	ft_parseendcondition(t_shell *msh, int n, int a, int k)
{
	int		i;

	msh->frk[n].cmds = ft_countendconditions(msh->frk[n].line, 0, 0);
	msh->frk[n].cmd = ft_calloc(10000 * sizeof(t_commands), 1);
	while (msh->frk[n].line[k] && a < msh->frk[n].cmds)
	{
		i = 0;
		msh->frk[n].cmd[a].line = ft_calloc(1000 * 8, 1);
		while (!ft_strchr("&|;\"\'", msh->frk[n].line[k]))
			msh->frk[n].cmd[a].line[i++] = msh->frk[n].line[k++];
		while (msh->frk[n].line[k] == '\"' || msh->frk[n].line[k] == '\'')
		{
			k = ft_cpquote(&(msh->frk[n].cmd[a].line), msh->frk[n].line, &i, k);
			if (msh->frk[n].line[k] == '\"' || msh->frk[n].line[k] == '\'')
				k = ft_cpquote(&(msh->frk[n].cmd[a].line), \
							msh->frk[n].line, &i, k);
			while (msh->frk[n].line[k]
				&& !ft_strchr("&|;", msh->frk[n].line[k]))
				msh->frk[n].cmd[a].line[i++] = msh->frk[n].line[k++];
		}
		msh->frk[n].cmd[a].line[i] = '\0';
		k = ft_foundcondition(msh, n, a, k);
		a++;
	}
	return (msh->frk[n]);
}
