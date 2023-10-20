/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   globsub.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: houtworm <codam@houtworm.net>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/20 03:29:24 by houtworm      #+#    #+#                 */
/*   Updated: 2023/10/20 17:38:17 by houtworm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_subjustaslash(t_globs *globs, char *dname, int i)
{
	char			*temp;
	char			*temp2;

	temp = ft_cpptostr(globs->tempsubdir);
	if (i == 0)
		temp2 = ft_vastrjoin(2, globs->pardir, dname);
	else
		temp2 = ft_vastrjoin(3, globs->pardir, dname, temp);
	ft_addglobmatch(globs, temp2);
	ft_vafree(2, temp, temp2);
	return (1);
}

void	ft_subcomparedir(t_globs *globs, struct dirent *dirents, int i, char *fullpath, char *dname)
{
	int		offset;
	int		j;
	char			*temp;
	char			*temp2;

	offset = 1;
	if ((globs->subdir[i][1] == '.' && dirents->d_name[0] == '.') || (globs->subdir[i][1] != '.' && dirents->d_name[0] != '.'))
	{
		j = 0;
		while (globs->subdir[i][j + offset] == '\\' || (dirents->d_name[j] && dirents->d_name[j] == globs->subdir[i][j + offset]))
		{
			if (globs->subdir[i][j + offset] == '\\')
			{
				offset++;
			}
			else
			{
				j++;
			}
		}
		if (globs->subdir[i][j + offset] && globs->subdir[i][j + offset - 1] != '\\' && ft_strchr("*?[", globs->subdir[i][j + offset]))
		{
			if (ft_firstsubglob(globs, dirents, i, j + offset))
			{
				free(globs->tempsubdir[i]);
				globs->tempsubdir[i] = ft_strjoin("/", dirents->d_name);
				if (!globs->subdir[i + 1])
				{
					temp = ft_cpptostr(globs->tempsubdir);
					temp2 = ft_vastrjoin(3, globs->pardir, dname, temp);
					ft_addglobmatch(globs, temp2);
					ft_vafree(2, temp, temp2);
				}
				else
				{
					if (dirents->d_type == DT_DIR)
					{
						free(globs->tempsubdir[i]);
						globs->tempsubdir[i] = ft_strjoin("/", dirents->d_name);
						temp = ft_vastrjoin(3, fullpath, "/", dirents->d_name);
						globs->temptype = dirents->d_type;
						ft_recursivematchsub(globs, temp, dname, i + 1);
						free(temp);
					}
				}
			}
		}
		if (globs->subdir[i][j + offset] == '\0' && dirents->d_name[j] == '\0')
		{
			if (!globs->subdir[i + offset])
			{
				free(globs->tempsubdir[i]);
				globs->tempsubdir[i] = ft_strjoin("/", dirents->d_name);
				temp = ft_cpptostr(globs->tempsubdir);
				temp2 = ft_vastrjoin(3, globs->pardir, dname, temp);
				ft_addglobmatch(globs, temp2);
				ft_vafree(2, temp, temp2);
			}
			else
			{
				if (dirents->d_type == DT_DIR)
				{
					free(globs->tempsubdir[i]);
					globs->tempsubdir[i] = ft_strjoin("/", dirents->d_name);
					temp = ft_vastrjoin(3, fullpath, "/", dirents->d_name);
					globs->temptype = dirents->d_type;
					ft_recursivematchsub(globs, temp, dname, i + 1);
					free(temp);
				}
			}
		}
	}
}

int	ft_recursivematchsub(t_globs *globs, char *fullpath, char *dname, int i)
{
	DIR				*dir;
	struct dirent	*dirents;

	if (globs->subdir[i][0] == '/' && globs->subdir[i][1] == '\0')
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
