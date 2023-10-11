/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   globsub.c                                       |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: houtworm <codam@houtworm.net>              //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/09/20 03:29:24 by houtworm     /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/10/11 13:30:51 by djonker      \___)=(___/                 */
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
		/*printf("here");*/
		temp = ft_cpptostr(globs->tempsubdir);
		if (i == 0)
			temp2 = ft_vastrjoin(2, globs->pardir, dname);
		else
			temp2 = ft_vastrjoin(3, globs->pardir, dname, temp);
		/*printf("pardir: %s\n", globs->pardir);*/
		/*printf("dname: %s\n", dname);*/
		/*printf("temp: %s\n", temp);*/
		ft_addglobmatch(globs, temp2); // add the match
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
			/*printf("starting in recursivematchsub with the following path %s trying to match %s\n", fullpath, dirents->d_name);*/
			/*printf("j: %d. offset: %d\n", j, offset);*/
			if ((globs->subdir[i][1] == '.' && dirents->d_name[0] == '.') || (globs->subdir[i][1] != '.' && dirents->d_name[0] != '.')) // if first character of globstart is not a .
			{
				j = 0;
				while (globs->subdir[i][j + offset] == '\\' || (dirents->d_name[j] && dirents->d_name[j] == globs->subdir[i][j + offset])) //just skip over the non globs
				{
					if (globs->subdir[i][j + offset] == '\\')
					{
						/*printf("ft_recursivematchsub found \\ skipping one character in subdir\n");*/
						offset++;
					}
					else
					{
						/*printf("ft_recursivematchsub fast match before glob: %c, %c\n", globs->subdir[i][j + offset], dirents->d_name[j]);*/
						j++;
					}
					// h*l*o
					//    ^
					// /h\*l\*o
					//      ^
				}
				/*printf("ft_recursivematchsub fast match broken: %c, %c\n", globs->subdir[i][j + offset], dirents->d_name[j]);*/
				if (globs->subdir[i][j + offset] && ft_strchr("*?[", globs->subdir[i][j + offset])) // we match the current character with a glob
				{
					/*printf("ft_recursivematchsub glob found for %s\n", dirents->d_name);*/
					if (ft_firstsubglob(globs, dirents, i, j + 1)) // returns a 1 if the glob matches eventually
					{
						free(globs->tempsubdir[i]);
						globs->tempsubdir[i] = ft_strjoin("/", dirents->d_name);
						/*printf("ft_recursivematchsub subdirs after recursive glob match: %s\n", ft_cpptostr(globs->tempsubdir));*/
						if (!globs->subdir[i + 1]) // if it is the last subdir
						{
							/*printf("ft_recursivematchsub no subdirectory remaining,adding %s%s to matches\n", dname, ft_cpptostr(globs->tempsubdir));*/
							temp = ft_cpptostr(globs->tempsubdir);
							temp2 = ft_vastrjoin(3, globs->pardir, dname, temp);
							ft_addglobmatch(globs, temp2); // add the match
							free(temp);
							free(temp2);
						}
						else
						{
							if (dirents->d_type == DT_DIR) // check if it is a directory
							{
								/*printf("ft_recursivematchsub %s is a directory going into recursion\n", dirents->d_name);*/
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
				if (globs->subdir[i][j + offset] == '\0' && dirents->d_name[j] == '\0') // glob matches completely
				{
					/*printf("ft_recursivematchsub %s matches completely\n", dirents->d_name);*/
					if (!globs->subdir[i + offset]) // if it is the last subdir
					{
						free(globs->tempsubdir[i]);
						globs->tempsubdir[i] = ft_strjoin("/", dirents->d_name);
						temp = ft_cpptostr(globs->tempsubdir);
						temp2 = ft_vastrjoin(3, globs->pardir, dname, temp);
						ft_addglobmatch(globs, temp2); // add the match
						free(temp);
						free(temp2);
					}
					else
					{
						if (dirents->d_type == DT_DIR) // check if it is a directory
						{
							free(globs->tempsubdir[i]);
							globs->tempsubdir[i] = ft_strjoin("/", dirents->d_name);
							/*printf("We need to go deeper here!!!\n");*/
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
