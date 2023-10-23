/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   subanyof.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: houtworm <codam@houtworm.net>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/20 00:51:38 by houtworm      #+#    #+#                 */
/*   Updated: 2023/10/23 14:08:42 by houtworm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_nextsubanyof(t_globs *globs, int si, int ri, int gi)
{
	gi = ft_matchanyof(globs->sdir[si], gi, globs->tmpsdir[si][ri]);
	if (gi == 0)
		return (0);
	else
		ri++;
	while (globs->sdir[si][gi] == '\\' || (globs->sdir[si][gi] && \
	globs->tmpsdir[si][ri] && globs->tmpsdir[si][ri] == globs->sdir[si][gi]))
	{
		if (globs->sdir[si][gi] != '\\')
			ri++;
		gi++;
	}
	if (globs->sdir[si][gi] == '\0' && globs->tmpsdir[si][ri] == '\0')
		if (globs->temptype == DT_DIR || !globs->sdir[si + 1])
			return (1);
	if (globs->sdir[si][gi - 1] != '\\' && globs->sdir[si][gi] && \
			ft_strchr("*?[", globs->sdir[si][gi]))
		return (ft_nextsubglob(globs, si, ri, gi));
	return (0);
}

int	ft_anyofgetrealpos(t_globs *globs, int si)
{
	int	ri;
	int	offset;

	ri = 0;
	offset = 0;
	while (globs->sdir[si][ri + offset])
	{
		if (globs->sdir[si][ri + offset] == '\\')
		{
			offset++;
			ri++;
		}
		else if (globs->sdir[si][ri + offset] == '[')
			return (ri);
		else
			ri++;
	}
	return (0);
}

int	ft_newtmpsubdir(t_globs *globs, int si, struct dirent *dirents)
{
	free(globs->tmpsdir[si]);
	globs->tmpsdir[si] = ft_strjoin("/", dirents->d_name);
	return (1);
}

int	ft_firstsubanyof(t_globs *globs, struct dirent *dirents, int si, int gi)
{
	int	ri;

	ri = ft_anyofgetrealpos(globs, si);
	gi = ft_matchanyof(globs->sdir[si], gi, dirents->d_name[ri - 1]);
	if (gi == 0)
		return (0);
	while (globs->sdir[si][gi] == '\\' || (globs->sdir[si][gi] && \
		dirents->d_name[ri] && dirents->d_name[ri] == globs->sdir[si][gi]))
	{
		if (globs->sdir[si][gi] != '\\')
			ri++;
		gi++;
	}
	if (dirents->d_name[ri] == '\0' && globs->sdir[si][gi] == '\0' && \
			(dirents->d_type == DT_DIR || !globs->sdir[si + 1]))
		return (ft_newtmpsubdir(globs, si, dirents));
	if (globs->sdir[si][gi] && ft_strchr("*?[", globs->sdir[si][gi]))
	{
		globs->temptype = dirents->d_type;
		ft_newtmpsubdir(globs, si, dirents);
		return (ft_nextsubglob(globs, si, ri + 1, gi));
	}
	return (0);
}
