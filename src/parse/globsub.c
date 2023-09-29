/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   globsub.c                                       |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: houtworm <codam@houtworm.net>              //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/09/20 03:29:24 by houtworm     /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/09/29 23:13:22 by houtworm     \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int		ft_recursivematchsub(t_globs *globs, char *fullpath, char *dname, int i)
{
	int				j;
	DIR				*dir;
	struct dirent	*dirents;

	j = 0;
	dir = opendir(fullpath);
	if (dir)
	{
		while ((dirents = readdir(dir)))
		{
			/*printf("starting in recursivematchsub with the following path %s trying to match %s\n", fullpath, dirents->d_name);*/
			if ((globs->subdir[i][0] == '.' && dirents->d_name[0] == '.') || (globs->subdir[i][0] != '.' && dirents->d_name[0] != '.')) // if first character of globstart is not a .
			{
				j = 0;
				while (dirents->d_name[j] && dirents->d_name[j] == globs->subdir[i][j + 1]) //just skip over the non globs
				{
					/*printf("ft_recursivematchsub fast match before glob: %c, %c\n", globs->subdir[i][j + 1], dirents->d_name[j]);*/
					j++;
				}
				/*printf("ft_recursivematchsub fast match broken: %c, %c\n", globs->subdir[i][j + 1], dirents->d_name[j]);*/
				if (globs->subdir[i][j + 1] && ft_strchr("*?[", globs->subdir[i][j + 1])) // we match the current character with a glob
				{
					/*printf("ft_recursivematchsub glob found for %s\n", dirents->d_name);*/
					if (ft_firstsubglob(globs, dirents, i, j + 1)) // returns a 1 if the glob matches eventually
					{
						globs->tempsubdir[i] = ft_strjoin("/", dirents->d_name);
						/*printf("ft_recursivematchsub subdirs after recursive glob match: %s\n", ft_cpptostr(globs->tempsubdir));*/
						if (!globs->subdir[i + 1]) // if it is the last subdir
						{
							/*printf("ft_recursivematchsub no subdirectory remaining,adding %s%s to matches\n", dname, ft_cpptostr(globs->tempsubdir));*/
							ft_addglobmatch(globs, ft_vastrjoin(3, globs->pardir, dname, ft_cpptostr(globs->tempsubdir))); // add the match
						}
						else
						{
							if (dirents->d_type == DT_DIR) // check if it is a directory
							{
								/*printf("ft_recursivematchsub %s is a directory going into recursion\n", dirents->d_name);*/
								globs->tempsubdir[i] = ft_strjoin("/", dirents->d_name);
								ft_recursivematchsub(globs, ft_vastrjoin(3, fullpath, "/", dirents->d_name), dname, i + 1);
							}
						}	
					}
				}
				if (globs->subdir[i][j + 1] == '\0' && dirents->d_name[j] == '\0') // glob matches completely
				{
					/*printf("ft_recursivematchsub %s matches completely\n", dirents->d_name);*/
					if (!globs->subdir[i + 1]) // if it is the last subdir
					{
						globs->tempsubdir[i] = ft_strjoin("/", dirents->d_name);
						ft_addglobmatch(globs, ft_vastrjoin(3, globs->pardir, dname, ft_cpptostr(globs->tempsubdir))); // add the match
					}
					else
					{
						if (dirents->d_type == DT_DIR) // check if it is a directory
						{
							globs->tempsubdir[i] = ft_strjoin("/", dirents->d_name);
							/*printf("We need to go deeper here!!!\n");*/
							ft_recursivematchsub(globs, ft_vastrjoin(3, fullpath, "/", dirents->d_name), dname, i + 1);
						}
					}
				}
			}
		}
		closedir(dir);
	}
	return (0);	
}
