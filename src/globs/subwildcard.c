/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   subwildcard.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: houtworm <codam@houtworm.net>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/27 08:14:23 by houtworm      #+#    #+#                 */
/*   Updated: 2023/10/20 19:34:43 by houtworm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_nextsubwildcard(t_globs *globs, int si, int ri, int gi)
{
	int	ti;

	while (globs->subdir[si][gi] == '*')
		gi++;
	if (globs->subdir[si][gi] == '\0')
		return (1);
	ti = gi;
	while (globs->tempsubdir[si][ri] && globs->subdir[si][gi])
	{
		if (globs->tempsubdir[si][ri] == globs->subdir[si][gi])
		{
			while (globs->subdir[si][gi] == '\\' || (globs->tempsubdir[si][ri] && globs->subdir[si][gi] && globs->tempsubdir[si][ri] == globs->subdir[si][gi]))
			{
				if (globs->subdir[si][gi] == '\\')
					gi++;
				else
				{
					gi++;
					ri++;
				}
			}
			if (globs->subdir[si][gi] == '\0')
			{
				if (globs->temptype == DT_DIR)
					return (1);
				else
				{
					if (globs->subdir[si + 1])
						return (0);
					else
						return (1);
				}
			}
			else if (globs->subdir[si][gi - 1] != '\\' && globs->subdir[si][gi] && ft_strchr("*?[", globs->subdir[si][gi]))
				return (ft_nextsubglob(globs, si, ri, gi));
			else
				gi = ti;
		}
		else if (globs->subdir[si][gi - 1] != '\\' && globs->subdir[si][gi] && ft_strchr("*?[", globs->subdir[si][gi]))
			return (ft_nextsubglob(globs, si, ri, gi));
		ri++;
	}
	return (0);
}

int	ft_firstsubwildcard(t_globs *globs, struct dirent *dirents, int si, int gi)
{
	int	ri;

	ri = gi - 1;
	while (globs->subdir[si][gi] == '*')
		gi++;
	if ((globs->subdir[si][0] == '.' && dirents->d_name[0] == '.') || (globs->subdir[si][0] != '.' && dirents->d_name[0] != '.'))
	{
		while (dirents->d_name[ri])
		{
			if (globs->subdir[si][gi] == '\0')
			{
				free(globs->tempsubdir[si]);
				globs->tempsubdir[si] = ft_strjoin("/", dirents->d_name);
				return (1);
			}
			while (globs->subdir[si][gi] == '\\' || (dirents->d_name[ri] && globs->subdir[si][gi] && dirents->d_name[ri] == globs->subdir[si][gi]))
			{
				if (globs->subdir[si][gi] == '\\')
					gi++;
				else
				{
					gi++;
					ri++;
				}
			}
			if (globs->subdir[si][gi] == '\0')
			{
				if (dirents->d_type == DT_DIR)
				{
					free(globs->tempsubdir[si]);
					globs->tempsubdir[si] = ft_strjoin("/", dirents->d_name);
					return (1);
				}
				else
				{
					if (globs->subdir[si + 1])
						return (0);
					else
					{
						free(globs->tempsubdir[si]);
						globs->tempsubdir[si] = ft_strjoin("/", dirents->d_name);
						return (1);
					}
				}
			}
			else if (globs->subdir[si][gi - 1] != '\\' && globs->subdir[si][gi] && ft_strchr("*?[", globs->subdir[si][gi]))
			{
				free(globs->tempsubdir[si]);
				globs->tempsubdir[si] = ft_strjoin("/", dirents->d_name);
				globs->temptype = dirents->d_type;
				if (ft_nextsubglob(globs, si, ri + 1, gi))
				{
					if (dirents->d_type == DT_DIR)
					{
						free(globs->tempsubdir[si]);
						globs->tempsubdir[si] = ft_strjoin("/", dirents->d_name);
						return (1);
					}
					else
					{
						if (globs->subdir[si + 1])
							return (0);
						else
						{
							free(globs->tempsubdir[si]);
							globs->tempsubdir[si] = ft_strjoin("/", dirents->d_name);
							return (1);
						}
					}
				}
				else if (globs->subdir[si][gi - 1] != '*' && globs->subdir[si][gi] == '?' && !globs->tempsubdir[si][ri + 3] && !globs->subdir[si][gi + 1])
					return (0);
			}
			ri++;
		}
	}
	return (0);
}
