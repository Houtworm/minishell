/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   subwildcard.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: houtworm <codam@houtworm.net>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/27 08:14:23 by houtworm      #+#    #+#                 */
/*   Updated: 2023/10/20 19:51:38 by houtworm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_nextsubwildcard(t_globs *globs, int si, int ri, int gi)
{
	int	ti;

	while (globs->sdir[si][gi] == '*')
		gi++;
	if (globs->sdir[si][gi] == '\0')
		return (1);
	ti = gi;
	while (globs->tmpsdir[si][ri] && globs->sdir[si][gi])
	{
		if (globs->tmpsdir[si][ri] == globs->sdir[si][gi])
		{
			while (globs->sdir[si][gi] == '\\' || (globs->tmpsdir[si][ri] && globs->sdir[si][gi] && globs->tmpsdir[si][ri] == globs->sdir[si][gi]))
			{
				if (globs->sdir[si][gi] == '\\')
					gi++;
				else
				{
					gi++;
					ri++;
				}
			}
			if (globs->sdir[si][gi] == '\0')
			{
				if (globs->temptype == DT_DIR)
					return (1);
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
			else
				gi = ti;
		}
		else if (globs->sdir[si][gi - 1] != '\\' && globs->sdir[si][gi] && ft_strchr("*?[", globs->sdir[si][gi]))
			return (ft_nextsubglob(globs, si, ri, gi));
		ri++;
	}
	return (0);
}

int	ft_firstsubwildcard(t_globs *globs, struct dirent *dirents, int si, int gi)
{
	int	ri;

	ri = gi - 1;
	while (globs->sdir[si][gi] == '*')
		gi++;
	if ((globs->sdir[si][0] == '.' && dirents->d_name[0] == '.') || (globs->sdir[si][0] != '.' && dirents->d_name[0] != '.'))
	{
		while (dirents->d_name[ri])
		{
			if (globs->sdir[si][gi] == '\0')
			{
				free(globs->tmpsdir[si]);
				globs->tmpsdir[si] = ft_strjoin("/", dirents->d_name);
				return (1);
			}
			while (globs->sdir[si][gi] == '\\' || (dirents->d_name[ri] && globs->sdir[si][gi] && dirents->d_name[ri] == globs->sdir[si][gi]))
			{
				if (globs->sdir[si][gi] == '\\')
					gi++;
				else
				{
					gi++;
					ri++;
				}
			}
			if (globs->sdir[si][gi] == '\0')
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
			else if (globs->sdir[si][gi - 1] != '\\' && globs->sdir[si][gi] && ft_strchr("*?[", globs->sdir[si][gi]))
			{
				free(globs->tmpsdir[si]);
				globs->tmpsdir[si] = ft_strjoin("/", dirents->d_name);
				globs->temptype = dirents->d_type;
				if (ft_nextsubglob(globs, si, ri + 1, gi))
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
				else if (globs->sdir[si][gi - 1] != '*' && globs->sdir[si][gi] == '?' && !globs->tmpsdir[si][ri + 3] && !globs->sdir[si][gi + 1])
					return (0);
			}
			ri++;
		}
	}
	return (0);
}
