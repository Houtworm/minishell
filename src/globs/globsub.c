/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   globsub.c                                       |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: houtworm <codam@houtworm.net>              //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/09/20 03:29:24 by houtworm     /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/10/14 06:12:20 by djonker      \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int		ft_recursivematchsub(t_globs *globs, char *fullpath, char *dname, int i)
{
	int				j;
	int				offset;
	DIR				*dir;
	struct dirent	*dirents;
	char			*temp;
	char			*temp2;

	j = 0;
	if (globs->subdir[i][0] == '/' && globs->subdir[i][1] == '\0')
	{
		temp = ft_cpptostr(globs->tempsubdir);
		if (i == 0)
			temp2 = ft_vastrjoin(2, globs->pardir, dname);
		else
			temp2 = ft_vastrjoin(3, globs->pardir, dname, temp);
		ft_addglobmatch(globs, temp2);
		free(temp);
		free(temp2);
		return (1);
	}
	dir = opendir(fullpath);
	if (dir)
	{
		while ((dirents = readdir(dir)))
		{
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
							free(temp);
							free(temp2);
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
						free(temp);
						free(temp2);
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
		closedir(dir);
	}
	return (0);	
}
