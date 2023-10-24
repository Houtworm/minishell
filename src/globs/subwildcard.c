/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   subwildcard.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: houtworm <codam@houtworm.net>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/27 08:14:23 by houtworm      #+#    #+#                 */
/*   Updated: 2023/10/24 02:30:08 by houtworm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_nextswcstartmatch(t_globs *globs, int si, int *ri, int *gi)
{
	while (globs->sdir[si][*gi] == '\\' || (globs->tmpsdir[si][*ri] && \
	globs->sdir[si][*gi] && globs->tmpsdir[si][*ri] == globs->sdir[si][*gi]))
	{
		if (globs->sdir[si][*gi] != '\\')
			(*ri)++;
		(*gi)++;
	}
	if (globs->sdir[si][*gi] == '\0')
	{
		if (globs->temptype == DT_DIR || !globs->sdir[si + 1])
			return (1);
		return (0);
	}
	else if (globs->sdir[si][*gi - 1] != '\\' && globs->sdir[si][*gi] && \
			ft_strchr("*?[", globs->sdir[si][*gi]))
		return (ft_nextsubglob(globs, si, *ri, *gi));
	else
		return (2);
}

int	ft_nextsubwildcard(t_globs *globs, int si, int ri, int gi)
{
	int	ti;
	int	ret;

	while (globs->sdir[si][gi] == '*')
		gi++;
	if (globs->sdir[si][gi] == '\0')
		return (1);
	ti = gi;
	while (globs->tmpsdir[si][ri] && globs->sdir[si][gi])
	{
		if (globs->tmpsdir[si][ri] == globs->sdir[si][gi])
		{
			ret = ft_nextswcstartmatch(globs, si, &ri, &gi);
			if (ret == 1)
				return (1);
			if (ret == 2)
				gi = ti;
		}
		else if (globs->sdir[si][gi - 1] != '\\' && globs->sdir[si][gi] && \
				ft_strchr("*?[", globs->sdir[si][gi]))
			return (ft_nextsubglob(globs, si, ri, gi));
		ri++;
	}
	return (0);
}

int	ft_foundanotherglob(t_globs *globs, struct dirent *dirents, int *srg)
{
	free(globs->tmpsdir[srg[0]]);
	globs->tmpsdir[srg[0]] = ft_strjoin("/", dirents->d_name);
	globs->temptype = dirents->d_type;
	if (ft_nextsubglob(globs, srg[0], srg[1] + 1, srg[2]))
	{
		if (dirents->d_type == DT_DIR || !globs->sdir[srg[0] + 1])
		{
			free(globs->tmpsdir[srg[0]]);
			globs->tmpsdir[srg[0]] = ft_strjoin("/", dirents->d_name);
			return (1);
		}
		return (2);
	}
	else if (globs->sdir[srg[0]][srg[2] - 1] != '*' && \
			globs->sdir[srg[0]][srg[2]] == '?' && \
			!globs->tmpsdir[srg[0]][srg[1] + 3] && \
			!globs->sdir[srg[0]][srg[2] + 1])
		return (2);
	return (0);
}

int	ft_attemptfromhere(t_globs *globs, struct dirent *dirents, int *srg)
{
	while (globs->sdir[srg[0]][srg[2]] == '\\' || \
	(dirents->d_name[srg[1]] && globs->sdir[srg[0]][srg[2]] && \
	dirents->d_name[srg[1]] == globs->sdir[srg[0]][srg[2]]))
	{
		if (globs->sdir[srg[0]][srg[2]] != '\\')
			srg[1]++;
		srg[2]++;
	}
	if (globs->sdir[srg[0]][srg[2]] == '\0')
	{
		if (dirents->d_type == DT_DIR || !globs->sdir[srg[0] + 1])
		{
			free(globs->tmpsdir[srg[0]]);
			globs->tmpsdir[srg[0]] = ft_strjoin("/", dirents->d_name);
			return (1);
		}
		return (2);
	}
	else if (globs->sdir[srg[0]][srg[2] - 1] != '\\' && \
	globs->sdir[srg[0]][srg[2]] && \
	ft_strchr("*?[", globs->sdir[srg[0]][srg[2]]))
		return (ft_foundanotherglob(globs, dirents, srg));
	return (0);
}

int	ft_firstsubwildcard(t_globs *globs, struct dirent *dirents, int si, int gi)
{
	int	*srg;
	int	ret;

	ret = 0;
	srg = ft_calloc(4, 16);
	srg[0] = si;
	srg[1] = gi - 1;
	srg[2] = gi;
	while (globs->sdir[si][srg[2]] == '*')
		srg[2]++;
	if ((globs->sdir[si][0] == '.' && dirents->d_name[0] == '.') || \
			(globs->sdir[si][0] != '.' && dirents->d_name[0] != '.'))
	{
		while (ret == 0 && dirents->d_name[srg[1]])
		{
			ret = ft_attemptfromhere(globs, dirents, srg);
			srg[1]++;
		}
	}
	free(srg);
	if (ret == 1)
		return (1);
	return (0);
}
