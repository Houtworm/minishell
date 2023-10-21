/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   subanyof.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: houtworm <codam@houtworm.net>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/20 00:51:38 by houtworm      #+#    #+#                 */
/*   Updated: 2023/10/21 09:16:27 by houtworm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_nextsubanyof(t_globs *globs, int si, int ri, int gi)
{
	int		l;

	l = 0;
	while (globs->sdir[si][gi] && globs->sdir[si][gi] != ']')
	{
		globs->anyof[l] = globs->sdir[si][gi];
		gi++;
		l++;
	}
	if (!globs->sdir[si][gi])
		return (0);
	globs->anyof[l] = '\0';
	if (globs->anyof[0] == '\0')
		return (0);
	if (ft_strchr(globs->anyof, globs->tmpsdir[si][ri]))
	{
		gi++;
		ri++;
	}
	while (globs->sdir[si][gi] == '\\' || (globs->sdir[si][gi] && globs->tmpsdir[si][ri] && globs->tmpsdir[si][ri] == globs->sdir[si][gi]))
	{
		if (globs->sdir[si][gi] != '\\')
			ri++;
		gi++;
	}
	if (globs->sdir[si][gi] == '\0' && globs->tmpsdir[si][ri] == '\0')
	{
		if (globs->temptype == DT_DIR)
		{
			return (1);
		}
		else
		{
			if (globs->sdir[si + 1])
				return (0);
			else
				return (1);
		}
	}
	else if (globs->sdir[si][gi - 1] != '\\' && globs->sdir[si][gi] && ft_strchr("*?[", globs->sdir[si][gi]))
		return (ft_nextsubglob(globs, si, ri, gi));
	return (0);
}

int	ft_firstsubanyof(t_globs *globs, struct dirent *dirents, int si, int gi)
{
	int	ri;

	ri = 0;
	while (globs->sdir[si][gi] && (globs->sdir[si][gi] != ']' || globs->sdir[si][gi - 1] == '\\'))
	{
		globs->anyof[ri] = globs->sdir[si][gi];
		ri++;
		gi++;
	}
	if (!globs->sdir[si][gi])
		return (0);
	globs->anyof[ri] = '\0';
	if (globs->anyof[0] == '\0')
		return (0);
	ri = 0;
	gi++;
	while (globs->sdir[si][ri + 1] != '[' || globs->sdir[si][ri] == '\\')
		ri++;
	if (ft_strchr(globs->anyof, dirents->d_name[ri]))
	{
		ri++;
		while (globs->sdir[si][gi] == '\\' || (globs->sdir[si][gi] && dirents->d_name[ri] && dirents->d_name[ri] == globs->sdir[si][gi]))
		{
			if (globs->sdir[si][gi] != '\\')
				ri++;
			gi++;
		}
		if (dirents->d_name[ri] == '\0' && globs->sdir[si][gi] == '\0')
		{
			if (dirents->d_type == DT_DIR)
			{
				free(globs->tmpsdir[si]);
				globs->tmpsdir[si] = ft_strjoin("/", dirents->d_name);
				return (1);
			}
			else
			{
				if (globs->sdir[si + 1])
					return (0);
				else
				{
					free(globs->tmpsdir[si]);
					globs->tmpsdir[si] = ft_strjoin("/", dirents->d_name);
					return (1);
				}
			}
		}
		if (dirents->d_name[ri] == '\0' || globs->sdir[si][gi] == '\0')
			return (0);
		if (globs->sdir[si][gi] && ft_strchr("*?[", globs->sdir[si][gi]))
		{
			globs->temptype = dirents->d_type;
			free(globs->tmpsdir[si]);
			globs->tmpsdir[si] = ft_strjoin("/", dirents->d_name);
			return (ft_nextsubglob(globs, si, ri + 1, gi));
		}
	}
	return (0);
}
