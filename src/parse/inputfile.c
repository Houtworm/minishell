/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   inputfile.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: houtworm <codam@houtworm.net>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/17 16:21:59 by houtworm      #+#    #+#                 */
/*   Updated: 2023/10/24 01:57:25 by houtworm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_infileinit( t_shell *msh, int f, int c, char *start)
{
	char	*end;
	char	*file;
	int		i;

	i = ft_strlen(start) + 1;
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

char	*ft_foundquote_infile(t_shell *msh, int f, int c, char *start)
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

int	ft_foundinfile(t_shell *msh, int frkn, int icmd, char *start)
{
	int		i;

	i = ft_strlen(start);
	if (msh->frk[frkn].cmd[icmd].line[i + 1] == '<')
	{
		if (ft_heredocinit(msh, frkn, icmd, start))
			return (130);
	}
	else
		if (ft_infileinit(msh, frkn, icmd, start))
			return (2);
	return (0);
}

int	ft_getstart_in(t_shell *msh, int frkn, int icmd, char *start)
{
	int		i;
	int		ret;

	i = 0;
	ret = 0;
	while (ret == 0 && msh->frk[frkn].cmd[icmd].line[i])
	{
		if (ft_strchr("\'\"", msh->frk[frkn].cmd[icmd].line[i]))
		{
			start = ft_foundquote_infile(msh, frkn, icmd, start);
			i = ft_strlen(start);
		}
		else if (msh->frk[frkn].cmd[icmd].line[i] == '<')
		{
			start[i] = '\0';
			ret = ft_foundinfile(msh, frkn, icmd, start);
			i = 0;
		}
		else
		{
			start[i] = msh->frk[frkn].cmd[icmd].line[i];
			i++;
		}
	}
	return (ret);
}

int	ft_parseinputfiles(t_shell *msh, int frkn)
{
	int		icmd;
	int		ret;
	char	*start;

	icmd = 0;
	ret = 0;
	start = ft_calloc(ft_strlen(msh->frk[frkn].cmd[icmd].line), 8);
	while (ret == 0 && icmd < msh->frk[frkn].cmds)
	{
		msh->frk[frkn].cmd[icmd].infiles = 0;
		if (ft_checkoutquote(msh->frk[frkn].cmd[icmd].line, '<', 2) >= 0)
			ret = ft_getstart_in(msh, frkn, icmd, start);
		icmd++;
	}
	free(start);
	return (ret);
}
