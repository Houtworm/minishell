/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   globsubdir.c                                       :+:      :+:    :+:   */
/*                                                     +:+                    */
/*   By: houtworm <codam@houtworm.net>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/20 03:29:24 by houtworm      #+#    #+#                 */
/*   Updated: 2023/10/21 12:19:13 by houtworm         ###   ########.fr       */
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

void	ft_subfoundglob(t_globs *globs, int i, int j, char *fullpath, struct dirent *dirents, char *dname)
{
	char	*temp;
	char	*temp2;

	if (ft_firstsubglob(globs, dirents, i, j))
	{
		free(globs->tmpsdir[i]);
		globs->tmpsdir[i] = ft_strjoin("/", dirents->d_name);
		if (!globs->sdir[i + 1])
		{
			temp = ft_cpptostr(globs->tmpsdir);
			temp2 = ft_vastrjoin(3, globs->pdir, dname, temp);
			ft_addglobmatch(globs, temp2);
			ft_vafree(2, temp, temp2);
		}
		else if (dirents->d_type == DT_DIR)
		{
			free(globs->tmpsdir[i]);
			globs->tmpsdir[i] = ft_strjoin("/", dirents->d_name);
			temp = ft_vastrjoin(3, fullpath, "/", dirents->d_name);
			globs->temptype = dirents->d_type;
			ft_recursivematchsub(globs, temp, dname, i + 1);
			free(temp);
		}
	}
}

void	ft_subatend(t_globs *globs, int i, int offset, char *fullpath, struct dirent *dirents, char *dname)
{
	char	*temp;
	char	*temp2;

	if (!globs->sdir[i + offset])
	{
		free(globs->tmpsdir[i]);
		globs->tmpsdir[i] = ft_strjoin("/", dirents->d_name);
		temp = ft_cpptostr(globs->tmpsdir);
		temp2 = ft_vastrjoin(3, globs->pdir, dname, temp);
		ft_addglobmatch(globs, temp2);
		ft_vafree(2, temp, temp2);
	}
	else if (dirents->d_type == DT_DIR)
	{
		free(globs->tmpsdir[i]);
		globs->tmpsdir[i] = ft_strjoin("/", dirents->d_name);
		temp = ft_vastrjoin(3, fullpath, "/", dirents->d_name);
		globs->temptype = dirents->d_type;
		ft_recursivematchsub(globs, temp, dname, i + 1);
		free(temp);
	}
}

void	ft_subcomparedir(t_globs *globs, struct dirent *dirents, int i, char *fullpath, char *dname)
{
	int		offset;
	int		j;

	offset = 1;
	if ((globs->sdir[i][1] == '.' && dirents->d_name[0] == '.') || (globs->sdir[i][1] != '.' && dirents->d_name[0] != '.'))
	{
		j = 0;
		while (globs->sdir[i][j + offset] == '\\' || (dirents->d_name[j] && dirents->d_name[j] == globs->sdir[i][j + offset]))
		{
			if (globs->sdir[i][j + offset] == '\\')
				offset++;
			else
				j++;
		}
		if (globs->sdir[i][j + offset] && globs->sdir[i][j + offset - 1] != '\\' && ft_strchr("*?[", globs->sdir[i][j + offset]))
			ft_subfoundglob(globs, i, j + offset, fullpath, dirents, dname);
		if (globs->sdir[i][j + offset] == '\0' && dirents->d_name[j] == '\0')
			ft_subatend(globs, i, offset, fullpath, dirents, dname);
	}
}

int	ft_recursivematchsub(t_globs *globs, char *fullpath, char *dname, int i)
{
	DIR				*dir;
	struct dirent	*dirents;

	if (globs->sdir[i][0] == '/' && globs->sdir[i][1] == '\0')
		return (ft_subjustaslash(globs, dname, i));
	dir = opendir(fullpath);
	if (dir)
	{
		dirents = readdir(dir);
		while (dirents)
		{
			ft_subcomparedir(globs, dirents, i, fullpath, dname);
			dirents = readdir(dir);
		}
		closedir(dir);
	}
	return (0);
}
