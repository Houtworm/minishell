/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc.c                                       |o_o || |                */
/*                                                     +:+                    */
/*   By: houtworm <codam@houtworm.net>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/12 11:25:43 by houtworm      #+#    #+#                 */
/*   Updated: 2023/10/18 03:48:59 by houtworm     \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*ft_getendheredoc(t_shell *msh, int forknumber, int icmd, int i)
{
	char	*end;
	int		j;

	j = 0;
	end = ft_calloc(ft_strlen(msh->frk[forknumber].cmd[icmd].line), 8);
	while (msh->frk[forknumber].cmd[icmd].line[i])
	{
		end[j] = msh->frk[forknumber].cmd[icmd].line[i];
		i++;
		j++;
	}
	end[j] = '\0';
	return (end);
}

char	*ft_getdelimiterheredoc(t_shell *msh, int f, int c, int i)
{
	int		j;
	char	*delimiter;

	delimiter = ft_calloc(ft_strlen(msh->frk[f].cmd[c].line), 8);
	while (msh->frk[f].cmd[c].line[i] == ' ')
		i++;
	j = 0;
	while (msh->frk[f].cmd[c].line[i] && msh->frk[f].cmd[c].line[i] != ' ')
	{
		delimiter[j] = msh->frk[f].cmd[c].line[i];
		i++;
		j++;
	}
	delimiter[j] = '\0';
	return (delimiter);
}

int	ft_getposheredoc(t_shell *msh, int f, int c, int i)
{
	while (msh->frk[f].cmd[c].line[i] == ' ')
		i++;
	while (msh->frk[f].cmd[c].line[i] && msh->frk[f].cmd[c].line[i] != ' ')
		i++;
	while (msh->frk[f].cmd[c].line[i] == ' ')
		i++;
	return (i);
}

void	ft_heredocinit(int i, t_shell *msh, int frki, int icmd, char *start)
{
	char	*delimiter;
	char	*cmdn;
	char	*frkn;
	char	*end;
	char	*tmp;

	i = i + 2;
	delimiter = ft_getdelimiterheredoc(msh, frki, icmd, i);
	i = ft_getposheredoc(msh, frki, icmd, i);
	frkn = ft_itoa(frki);
	cmdn = ft_itoa(icmd);
	tmp = ft_vastrjoin(7, msh->tmpdir, "heredoc", ".", frkn, ".", cmdn, ".tmp");
	free(frkn);
	free(cmdn);
	ft_heredoc(delimiter, tmp, *msh, msh->frk[frki].cmd[icmd].infiles);
	msh->frk[frki].cmd[icmd].infiles++;
	free(tmp);
	free(delimiter);
	end = ft_getendheredoc(msh, frki, icmd, i);
	free (msh->frk[frki].cmd[icmd].line);
	msh->frk[frki].cmd[icmd].line = ft_strjoin(start, end);
	free(end);
}
