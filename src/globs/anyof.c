/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   anyof.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: houtworm <codam@houtworm.net>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/20 00:51:38 by houtworm      #+#    #+#                 */
/*   Updated: 2023/10/19 06:18:53 by djonker       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_nextsubanyof(t_globs *globs, int si, int ri, int gi)
{
	int		l;

	l = 0;
	while (globs->subdir[si][gi] && globs->subdir[si][gi] != ']')
	{
		globs->anyof[l] = globs->subdir[si][gi];
		gi++;
		l++;
	}
	if (!globs->subdir[si][gi])
		return (0);
	globs->anyof[l] = '\0';
	if (globs->anyof[0] == '\0')
		return (0);
	if (ft_strchr(globs->anyof, globs->tempsubdir[si][ri]))
	{
		gi++;
		ri++;
	}
	while (globs->subdir[si][gi] == '\\' || (globs->subdir[si][gi] && globs->tempsubdir[si][ri] && globs->tempsubdir[si][ri] == globs->subdir[si][gi]))
	{
		if (globs->subdir[si][gi] == '\\')
			gi++;
		else
		{
			ri++;
			gi++;
		}
	}
	if (globs->subdir[si][gi] == '\0' && globs->tempsubdir[si][ri] == '\0')
	{
		if (globs->temptype == DT_DIR)
		{
			return (1);
		}
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
	return (0);
}

int	ft_firstsubanyof(t_globs *globs, struct dirent *dirents, int si, int gi)
{
	int	ri;

	ri = 0;
	while (globs->subdir[si][gi] && (globs->subdir[si][gi] != ']' || globs->subdir[si][gi - 1] == '\\'))
	{
		globs->anyof[ri] = globs->subdir[si][gi];
		ri++;
		gi++;
	}
	if (!globs->subdir[si][gi])
		return (0);
	globs->anyof[ri] = '\0';
	if (globs->anyof[0] == '\0')
		return (0);
	ri = 0;
	gi++;
	while (globs->subdir[si][ri + 1] != '[' || globs->subdir[si][ri] == '\\')
		ri++;
	if (ft_strchr(globs->anyof, dirents->d_name[ri]))
	{
		ri++;
		while (globs->subdir[si][gi] == '\\' || (globs->subdir[si][gi] && dirents->d_name[ri] && dirents->d_name[ri] == globs->subdir[si][gi]))
		{
			if (globs->subdir[si][gi] == '\\')
				gi++;
			else
			{
				gi++;
				ri++;
			}
		}
		if (dirents->d_name[ri] == '\0' && globs->subdir[si][gi] == '\0')
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
		if (dirents->d_name[ri] == '\0' || globs->subdir[si][gi] == '\0')
			return (0);
		if (globs->subdir[si][gi] && ft_strchr("*?[", globs->subdir[si][gi]))
		{
			globs->temptype = dirents->d_type;
			free(globs->tempsubdir[si]);
			globs->tempsubdir[si] = ft_strjoin("/", dirents->d_name);
			return (ft_nextsubglob(globs, si, ri + 1, gi));
		}
	}
	return (0);
}

int	ft_nextanyof(t_globs *globs, char *dname, int ri, int gi)
{
	char	match;
	int		k;

	k = 0;
	match = dname[ri];
	while (globs->gend[gi] && globs->gend[gi] != ']')
	{
		globs->anyof[k] = globs->gend[gi];
		gi++;
		k++;
	}
	if (!globs->gend[gi])
		return (0);
	globs->anyof[k] = '\0';
	if (globs->anyof[0] == '\0')
		return (0);
	if (ft_strchr(globs->anyof, match))
	{
		gi++;
		ri++;
	}
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
	{
		return (ft_nextglob(globs, dname, ri, gi));
	}
	if (globs->gend[gi] == '\0' && dname[ri] == '\0')
		return (1);
	return (0);
}

int	ft_firstanyof(t_globs *globs, char *dname, int ri)
{
	int		gi;
	char	*temp;

	gi = 0;
	if (!globs->anyof[0])
	{
		while (globs->gend[gi] && globs->gend[gi] != ']')
		{
			globs->glob[gi + 1] = globs->gend[gi];
			globs->anyof[gi] = globs->gend[gi];
			gi++;
		}
		if (!globs->gend[gi])
			return (0);
		globs->anyof[gi] = '\0';
		globs->glob[gi + 1] = ']';
		temp = ft_substr(globs->gend, gi + 1, ft_strlen(globs->gend));
		free(globs->gend);
		globs->gend = ft_strdup(temp);
		free(temp);
	}
	else
	{
		while (globs->glob[gi + 1] && globs->glob[gi + 1] != ']')
		{
			globs->anyof[gi] = globs->glob[gi + 1];
			gi++;
		}
		if (!globs->glob[gi + 1])
			return (0);
		globs->anyof[gi] = '\0';
	}
	if (globs->anyof[0] == '\0')
		return (0);
	if (ft_strchr(globs->anyof, dname[ri]))
	{
		gi = 0;
		ri++;
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
	}
	return (0);
}
