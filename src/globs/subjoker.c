/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   subjoker.c                                         :+:      :+:    :+:   */
/*                                                     +:+                    */
/*   By: houtworm <codam@houtworm.net>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/20 00:51:17 by houtworm      #+#    #+#                 */
/*   Updated: 2023/10/21 12:47:14 by houtworm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_nextsubjoker(t_globs *globs, int si, int ri, int gi)
{
	while (globs->sdir[si][gi] == '\\' || (globs->tmpsdir[si][ri] && \
		globs->sdir[si][gi] && globs->tmpsdir[si][ri] == globs->sdir[si][gi]))
	{
		if (globs->sdir[si][gi] != '\\')
			ri++;
		gi++;
	}
	if (globs->sdir[si][gi] == '\0' && globs->tmpsdir[si][ri] == '\0')
	{
		if (globs->temptype == DT_DIR || !globs->sdir[si + 1])
			return (1);
		return (0);
	}
	if (globs->sdir[si][gi - 1] != '\\' && globs->sdir[si][gi] == '*' && \
			globs->tmpsdir[si][ri] == '\0')
		return (ft_nextsubglob(globs, si, ri, gi));
	if (globs->sdir[si][gi] == '\0' || globs->tmpsdir[si][ri] == '\0')
		return (0);
	else if (globs->sdir[si][gi - 1] != '\\' && globs->sdir[si][gi] && \
			ft_strchr("*?[", globs->sdir[si][gi]))
		return (ft_nextsubglob(globs, si, ri, gi));
	return (0);
}

int	ft_fsubjokerfglob(t_globs *globs, struct dirent *dirents, int si, int gi)
{
	free(globs->tmpsdir[si]);
	globs->tmpsdir[si] = ft_strjoin("/", dirents->d_name);
	globs->temptype = dirents->d_type;
	if (ft_nextsubglob(globs, si, gi, gi))
	{
		if (dirents->d_type == DT_DIR || !globs->sdir[si + 1])
		{
			free(globs->tmpsdir[si]);
			globs->tmpsdir[si] = ft_strjoin("/", dirents->d_name);
			return (1);
		}
	}
	return (0);
}

int	ft_firstsubjoker(t_globs *globs, struct dirent *dirents, int si, int gi)
{
	int		ri;

	ri = gi - 1;
	if ((globs->sdir[si][0] == '.' && dirents->d_name[0] == '.') || (globs->sdir[si][0] != '.' && dirents->d_name[0] != '.'))
	{
		while (globs->sdir[si][gi] == '\\' || (dirents->d_name[ri] && globs->sdir[si][gi] && dirents->d_name[ri] == globs->sdir[si][gi]))
		{
			if (globs->sdir[si][gi] != '\\')
				ri++;
			gi++;
		}
		if (globs->sdir[si][gi] == '\0' && dirents->d_name[ri] == '\0')
		{
			if (dirents->d_type == DT_DIR || !globs->sdir[si + 1])
			{
				free(globs->tmpsdir[si]);
				globs->tmpsdir[si] = ft_strjoin("/", dirents->d_name);
				return (1);
			}
		}
		if (globs->sdir[si][gi] && ft_strchr("*?[", globs->sdir[si][gi]))
			if (ft_fsubjokerfglob(globs, dirents, si, gi))
				return (1);
	}
	return (0);
}
