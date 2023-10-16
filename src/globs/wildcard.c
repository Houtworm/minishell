/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   wildcard.c                                      |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: houtworm <codam@houtworm.net>              //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/08/27 08:14:23 by houtworm     /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/10/16 10:51:40 by houtworm     \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int		ft_nextsubwildcard(t_globs *globs, int si, int ri, int gi)
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

int		ft_firstsubwildcard(t_globs *globs, struct dirent *dirents, int si, int gi)
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
			while (globs->subdir[si][gi] == '\\' || (dirents->d_name[ri] && globs->subdir[si][gi] && dirents->d_name[ri] == globs->subdir[si][gi])) //while the characters match we skip them
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

int	ft_nextwildcard(t_globs *globs, char *dname, int ri, int gi)
{
	int		tempj;
	int		tempi;

	while (globs->gend[gi] == '*')
		gi++;
	tempj = gi;
	tempi = ri;
	if (globs->gend[gi] == '\0')
		return (1);
	while (dname[ri])
	{
		if (globs->gend[gi] == '\\' || dname[ri] == globs->gend[gi])
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
			if (globs->gend[gi - 1] != '\\' && globs->gend[gi] && ft_strchr("*?[", globs->gend[gi]))
				return (ft_nextglob(globs, dname, ri, gi));
			if (dname[ri] == '\0')
				return (1);
			else
				gi = tempj;
		}
		if (globs->gend[gi - 1] != '\\' && globs->gend[gi] && ft_strchr("*?[", globs->gend[gi]))
			return (ft_nextglob(globs, dname, ri, gi));
		tempi++;
		ri = tempi;
	}
	return (0);
}

int	ft_firstwildcard(t_globs *globs, char *dname, int ri)
{
	int	temp;
	int	ret;
	int	gi;

	gi = 0;
	temp = ri;
	if (globs->gstart[0] != '.' && dname[0] == '.')
		return (0);
	while (globs->gend[gi] == '*')
		gi++;
	if (globs->gend[gi] == '\0' && dname[ri] == '\0')
		return (1);
	while (dname[ri])
	{
		while (globs->gend[gi] == '*')
			gi++;
		if (dname[ri] == globs->gend[gi] || globs->gend[0] == '\0')
		{
			if (globs->gend[0] == '\0')
				return (1);
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
			{
				return (1);
			}
			if (globs->gend[gi - 1] != '\\' && globs->gend[gi] && ft_strchr("*?[", globs->gend[gi]))
			{
				ret = ft_nextglob(globs, dname, ri, gi);
				if (ret == 1)
					return (ret);
				ri++;
				gi = 0;
			}
			else
			{
				ri++;
				gi = 0;
			}
		}
		else if (ft_strchr("*?[", globs->gend[gi]))
		{
			ret = ft_nextglob(globs, dname, ri, gi);
			if (ret == 1)
				return (ret);
			temp++;
			ri = temp;
		}
		else
		{
			temp++;
			ri = temp;
		}
	}
	return (0);
}
