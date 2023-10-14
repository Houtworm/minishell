/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   joker.c                                         |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: houtworm <codam@houtworm.net>              //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/09/20 00:51:17 by houtworm     /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/10/14 06:37:20 by djonker      \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int		ft_nextsubjoker(t_globs *globs, int si, int ri, int gi)
{
	while (globs->subdir[si][gi] == '\\' || (globs->tempsubdir[si][ri] && globs->subdir[si][gi] && globs->tempsubdir[si][ri] == globs->subdir[si][gi])) //while the characters match we skip them
	{
		if (globs->subdir[si][gi] == '\\')
			gi++;
		else
		{
			gi++;
			ri++;
		}
	}
	if (globs->subdir[si][gi] == '\0' && globs->tempsubdir[si][ri] == '\0')
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
	if (globs->subdir[si][gi - 1] != '\\' && globs->subdir[si][gi] == '*' && globs->tempsubdir[si][ri] == '\0')
	{
		return (ft_nextsubglob(globs, si, ri, gi));
	}
	if (globs->subdir[si][gi] == '\0' || globs->tempsubdir[si][ri] == '\0')
	{
		return (0);
	}
	else if (globs->subdir[si][gi - 1] != '\\' && globs->subdir[si][gi] && ft_strchr("*?[", globs->subdir[si][gi]))
	{
		return (ft_nextsubglob(globs, si, ri, gi));
	}
	return (0);
}

int		ft_firstsubjoker(t_globs *globs, struct dirent *dirents, int si, int gi)
{
	int		ri;

	ri = gi - 1;
	if ((globs->subdir[si][0] == '.' && dirents->d_name[0] == '.') || (globs->subdir[si][0] != '.' && dirents->d_name[0] != '.'))
	{
		while (globs->subdir[si][gi] == '\\' || (dirents->d_name[ri] && globs->subdir[si][gi] && dirents->d_name[ri] == globs->subdir[si][gi]))
		{
			if (globs->subdir[si][gi] == '\\')
				gi++;
			else
				gi++;
		}
		if (globs->subdir[si][gi] == '\0' && dirents->d_name[ri] == '\0')
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
				{
					return (0);
				}
				else
				{
					free(globs->tempsubdir[si]);
					globs->tempsubdir[si] = ft_strjoin("/", dirents->d_name);
					return (1);
				}
			}
		}
		if (globs->subdir[si][gi] == '\0' && dirents->d_name[ri] == '\0')
			return (1);
		if (globs->subdir[si][gi] == '\0' || dirents->d_name[gi - 1] == '\0')
			return (0);
		if (globs->subdir[si][gi] && ft_strchr("*?[", globs->subdir[si][gi]))
		{
			free(globs->tempsubdir[si]);
			globs->tempsubdir[si] = ft_strjoin("/", dirents->d_name);
			globs->temptype = dirents->d_type;
			if (ft_nextsubglob(globs, si, gi, gi))
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
			else
				return (0);
		}
	}
	return (0);
}

int	ft_nextjoker(t_globs *globs, char *dname, int ri, int gi)
{
	while (globs->gend[gi] == '\\' || (dname[ri] && globs->gend[gi] && dname[ri] == globs->gend[gi]))
	{
		if (globs->gend[gi] == '\\')
			gi++;
		else
		{
			gi++;
			ri++;
		}
	}
	if (dname[ri] && globs->gend[gi] && ft_strchr("*?[", globs->gend[gi]) && globs->gend[gi - 1] != '\\')
		return (ft_nextglob(globs, dname, ri, gi));
	if (globs->gend[gi] == '\0' && dname[ri] == '\0')
		return (1);
	if (globs->gend[gi - 1] != '\\' && globs->gend[gi] == '*' && dname[ri] == '\0')
		return (ft_nextglob(globs, dname, ri, gi));
	if (globs->gend[gi] == '\0' || dname[ri] == '\0')
		return (0);
	return (0);
}

int	ft_firstjoker(t_globs *globs, char *dname, int ri)
{
	int	gi;

	gi = 0;
	if (globs->gstart[0] != '.' && dname[0] == '.')
		return (0);
	while (globs->gend[gi] == '\\' || (dname[ri] && globs->gend[gi] && dname[ri] == globs->gend[gi]))
	{
		if (globs->gend[gi] == '\\')
			gi++;
		else
		{
			gi++;
			ri++;
		}
	}
	if (dname[ri] == '\0' && globs->gend[gi] == '\0')
		return (1);
	if (dname[ri] == '\0' || globs->gend[gi] == '\0')
		return (0);
	if (ft_strchr("*?[", globs->gend[gi]))
		return (ft_nextglob(globs, dname, ri, gi));
	return (0);
}
