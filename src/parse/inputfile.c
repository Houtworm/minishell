/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   inputfile.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: houtworm <codam@houtworm.net>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/17 16:21:59 by houtworm      #+#    #+#                 */
/*   Updated: 2023/10/18 17:01:10 by houtworm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"


int	ft_infileinit(int i, t_shell *msh, int f, int c, char *start)
{
	char	*end;
	char	*file;

	i++;
	while (msh->frk[f].cmd[c].line[i] && msh->frk[f].cmd[c].line[i] == ' ')
		i++;
	file = ft_getfileinputfile(msh, f, c, i);
	i = ft_getfilepos(msh, f, c, i);
	file = ft_parsetilde(file, *msh);
	if (ft_checkinputfile(file))
	{
		free(file);
		return (2);
	}
	ft_writefiletoinput(msh, f, c, file);
	end = ft_getendinputfile(msh, f, c, i);
	free (msh->frk[f].cmd[c].line);
	msh->frk[f].cmd[c].line = ft_strjoin(start, end);
	ft_vafree(2, end, file, start);
	return (0);
}

char	*ft_foundquoteinputfile(t_shell *msh, int f, int c, char *start)
{
	char	quote;
	int		i;

	i = ft_strlen(start);
	quote = msh->frk[f].cmd[c].line[i];
	start[i] = msh->frk[f].cmd[c].line[i];
	i++;
	while (msh->frk[f].cmd[c].line[i] && msh->frk[f].cmd[c].line[i] != quote)
	{
		start[i] = msh->frk[f].cmd[c].line[i];
		i++;
	}
	start[i] = msh->frk[f].cmd[c].line[i];
	i++;
	return (start);
}

int	ft_foundinputfile(t_shell *msh, int frkn, int icmd, char *start)
{
	int		i;

	i = ft_strlen(start);
	if (msh->frk[frkn].cmd[icmd].line[i + 1] == '<')
		ft_heredocinit(i, msh, frkn, icmd, start);
	else
		if (ft_infileinit(i, msh, frkn, icmd, start))
			return (2);
	return (0);
}

char	*ft_getstart(t_shell *msh, int frkn, int icmd, char *start)
{
	int		i;

	i = 0;
	while (msh->frk[frkn].cmd[icmd].line[i])
	{
		if (ft_strchr("\'\"", msh->frk[frkn].cmd[icmd].line[i]))
		{
			start = ft_foundquoteinputfile(msh, frkn, icmd, start);
			i = ft_strlen(start);
		}
		else if (msh->frk[frkn].cmd[icmd].line[i] == '<')
		{
			start[i] = '\0';
			if (ft_foundinputfile(msh, frkn, icmd, start))
				return (NULL);
			i = 0;
		}
		else
		{
			start[i] = msh->frk[frkn].cmd[icmd].line[i];
			i++;
		}
	}
	return (start);
}

int ft_parseinputfiles(t_shell *msh, int frkn)
{
	int		icmd;
	char	*start;

	icmd = 0;
	start = ft_calloc(ft_strlen(msh->frk[frkn].cmd[icmd].line), 8);
	while (icmd < msh->frk[frkn].cmdamount)
	{
		msh->frk[frkn].cmd[icmd].infiles = 0;
		if (ft_checkoutquote(msh->frk[frkn].cmd[icmd].line, '<', 2) >= 0)
		{
			start = ft_getstart(msh, frkn, icmd, start);
			if (!start)
				return (2);
		}
		icmd++;
	}
	free(start);
	return (0);
}
