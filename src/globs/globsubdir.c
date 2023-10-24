/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   globsubdir.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: houtworm <codam@houtworm.net>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/20 03:29:24 by houtworm      #+#    #+#                 */
/*   Updated: 2023/10/25 01:39:59 by djonker       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_subjustaslash(t_globs *globs, char *dname, int i)
{
	char	*temp;
	char	*temp2;

	temp = ft_cpptostr(globs->tmpsdir);
	if (i == 0)
		temp2 = ft_vastrjoin(2, globs->pdir, dname);
	else
		temp2 = ft_vastrjoin(3, globs->pdir, dname, temp);
	ft_addglobmatch(globs, temp2);
	ft_vafree(2, temp, temp2);
	return (1);
}

void	ft_subfoundglob(t_globs *glo, int *ij, char *fpath, struct dirent *drt)
{
	char	*temp;
	char	*temp2;

	if (ft_firstsubglob(glo, drt, ij[0], ij[1] + ij[2]))
	{
		free(glo->tmpsdir[ij[0]]);
		glo->tmpsdir[ij[0]] = ft_strjoin("/", drt->d_name);
		if (!glo->sdir[ij[0] + 1])
		{
			temp = ft_cpptostr(glo->tmpsdir);
			temp2 = ft_vastrjoin(3, glo->pdir, glo->dname, temp);
			ft_addglobmatch(glo, temp2);
			ft_vafree(2, temp, temp2);
		}
		else if (drt->d_type == DT_DIR)
		{
			free(glo->tmpsdir[ij[0]]);
			glo->tmpsdir[ij[0]] = ft_strjoin("/", drt->d_name);
			temp = ft_vastrjoin(3, fpath, "/", drt->d_name);
			glo->temptype = drt->d_type;
			ft_recursivematchsub(glo, temp, ij[0] + 1);
			free(temp);
		}
	}
}

void	ft_subatend(t_globs *globs, int *ij, char *fpath, struct dirent *drt)
{
	char	*temp;
	char	*temp2;

	if (!globs->sdir[ij[0] + ij[2]])
	{
		free(globs->tmpsdir[ij[0]]);
		globs->tmpsdir[ij[0]] = ft_strjoin("/", drt->d_name);
		temp = ft_cpptostr(globs->tmpsdir);
		temp2 = ft_vastrjoin(3, globs->pdir, globs->dname, temp);
		ft_addglobmatch(globs, temp2);
		ft_vafree(2, temp, temp2);
	}
	else if (drt->d_type == DT_DIR)
	{
		free(globs->tmpsdir[ij[0]]);
		globs->tmpsdir[ij[0]] = ft_strjoin("/", drt->d_name);
		temp = ft_vastrjoin(3, fpath, "/", drt->d_name);
		globs->temptype = drt->d_type;
		ft_recursivematchsub(globs, temp, ij[0] + 1);
		free(temp);
	}
}

void	ft_subcomparedir(t_globs *globs, struct dirent *drt, int i, char *fpath)
{
	int		ij[3];

	ij[0] = i;
	ij[2] = 1;
	if ((globs->sdir[i][1] == '.' && drt->d_name[0] == '.') || \
			(globs->sdir[i][1] != '.' && drt->d_name[0] != '.'))
	{
		ij[1] = 0;
		while (globs->sdir[i][ij[1] + ij[2]] == '\\' || \
				(drt->d_name[ij[1]] && \
					drt->d_name[ij[1]] == globs->sdir[i][ij[1] + ij[2]]))
		{
			if (globs->sdir[i][ij[1] + ij[2]] == '\\')
				ij[2]++;
			else
				ij[1]++;
		}
		if (globs->sdir[i][ij[1] + ij[2]] && \
				globs->sdir[i][ij[1] + ij[2] - 1] != '\\' && \
				ft_strchr("*?[", globs->sdir[i][ij[1] + ij[2]]))
			ft_subfoundglob(globs, ij, fpath, drt);
		if (globs->sdir[i][ij[1] + ij[2]] == '\0' \
				&& drt->d_name[ij[1]] == '\0')
			ft_subatend(globs, ij, fpath, drt);
	}
}

int	ft_recursivematchsub(t_globs *globs, char *fullpath, int i)
{
	DIR				*dir;
	struct dirent	*dirents;

	if (globs->sdir[i][0] == '/' && globs->sdir[i][1] == '\0')
		return (ft_subjustaslash(globs, globs->dname, i));
	dir = opendir(fullpath);
	if (dir)
	{
		dirents = readdir(dir);
		while (dirents)
		{
			ft_subcomparedir(globs, dirents, i, fullpath);
			dirents = readdir(dir);
		}
		closedir(dir);
	}
	return (0);
}
