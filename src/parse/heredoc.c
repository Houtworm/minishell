/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: houtworm <codam@houtworm.net>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/12 11:25:43 by houtworm      #+#    #+#                 */
/*   Updated: 2023/10/24 02:05:06 by houtworm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*ft_getdelimiterheredoc(t_shell *msh, int f, int c, int i)
{
	int		j;
	char	*delimiter;

	delimiter = ft_calloc(ft_strlen(msh->frk[f].cmd[c].line), 8);
	while (msh->frk[f].cmd[c].line[i] == ' ')
		i++;
	j = 0;
	while (msh->frk[f].cmd[c].line[i] && msh->frk[f].cmd[c].line[i] != ' '
		&& msh->frk[f].cmd[c].line[i] != '<')
	{
		delimiter[j] = msh->frk[f].cmd[c].line[i];
		i++;
		j++;
	}
	delimiter[j] = '\0';
	return (delimiter);
}

char	*ft_getendheredoc(t_shell *msh, int frki, int icmd, int i)
{
	char	*end;
	int		j;

	j = 0;
	while (msh->frk[frki].cmd[icmd].line[i] == ' ')
		i++;
	while (msh->frk[frki].cmd[icmd].line[i]
		&& msh->frk[frki].cmd[icmd].line[i] != ' '
		&& msh->frk[frki].cmd[icmd].line[i] != '<')
		i++;
	while (msh->frk[frki].cmd[icmd].line[i] == ' ')
		i++;
	end = ft_calloc(ft_strlen(msh->frk[frki].cmd[icmd].line), 8);
	while (msh->frk[frki].cmd[icmd].line[i])
	{
		end[j] = msh->frk[frki].cmd[icmd].line[i];
		i++;
		j++;
	}
	end[j] = '\0';
	return (end);
}

int	ft_heredocinit(t_shell *msh, int frki, int icmd, char *start)
{
	char	*delimiter;
	char	*cmdn;
	char	*frkn;
	char	*end;
	char	*tmp;

	delimiter = ft_getdelimiterheredoc(msh, frki, icmd, ft_strlen(start) + 2);
	frkn = ft_itoa(frki);
	cmdn = ft_itoa(icmd);
	tmp = ft_vastrjoin(7, msh->tmpdir, "heredoc", ".", frkn, ".", cmdn, ".tmp");
	ft_vafree(2, frkn, cmdn);
	if (ft_heredoc(delimiter, tmp, *msh, msh->frk[frki].cmd[icmd].infiles))
	{
		ft_vafree(2, tmp, delimiter);
		return (1);
	}
	msh->frk[frki].cmd[icmd].infiles++;
	end = ft_getendheredoc(msh, frki, icmd, ft_strlen(start) + 2);
	ft_vafree(3, tmp, delimiter, msh->frk[frki].cmd[icmd].line);
	msh->frk[frki].cmd[icmd].line = ft_strjoin(start, end);
	free(end);
	return (0);
}
