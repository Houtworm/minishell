/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   joker.c                                         |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: houtworm <codam@houtworm.net>              //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/09/20 00:51:17 by houtworm     /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/09/20 03:51:14 by houtworm     \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int		ft_recursivesubjoker(t_globs *globs, struct dirent *dirents, int i, int j)
{
	if ((globs->subdir[i][0] == '.' && dirents->d_name[0] == '.') || (globs->subdir[i][0] != '.' && dirents->d_name[0] != '.')) // if first character of globstart is not a .
	{
		printf("ft_recursivesubjoker periods match for %s\n", dirents->d_name);
		if (globs->subdir[i][j] == '\0' || dirents->d_name[j] == '\0') // the whole filename matches
		{
			printf("ft_recursivesubjoker just a * so %s is an easy match\n", dirents->d_name);
			globs->tempsubdir[i] = ft_strjoin("/", dirents->d_name);
			return (1); // copy it over.
		}
		while (dirents->d_name[j]) // while there are characters in filename 
		{
			while (dirents->d_name[j] && globs->subdir[i][j + 1] && dirents->d_name[j] == globs->subdir[i][j + 1]) //while the characters match we skip them
			{
				printf("ft_recursivesubjoker fastmatch: %c, %c\n", globs->subdir[i][j + 1], dirents->d_name[j]);
				j++;
			}
			printf("ft_recursivesubjoker fastmatch broken: %c, %c\n", globs->subdir[i][j + 1], dirents->d_name[j]);
			if (globs->subdir[i][j + 1] == '\0') // if the end matches too
			{
				if (dirents->d_type == DT_DIR) // check if it is a directory
				{
					printf("ft_recursivesubjoker glob matches %s will be replaced with /%s in subdir %d\n", globs->subdir[i], dirents->d_name, i);
					globs->tempsubdir[i] = ft_strjoin("/", dirents->d_name);
					return (1); // this one is a match
					// I think we should branch out here, match all the following subdirs....
				}
				else
				{
					if (globs->subdir[i + 1])
					{
						printf("ft_recursivesubjoker %s is not a dir and we need to go deeper so no match\n", dirents->d_name);
						return (0);
					}
					else
					{
						globs->tempsubdir[i] = ft_strjoin("/", dirents->d_name);
						printf("ft_recursivesubjoker %s matches but is not a dir but we are at our dept so match\n", dirents->d_name);
						return (1);
					}
				}
			}
			if (ft_strchr("*?[", globs->subdir[i][j + 1])) // if we find a new glob
			{
				printf("ft_recursivesubjoker found glob going into recursion\n");
				globs->tempsubdir[i] = ft_strjoin("/", dirents->d_name);
				return (ft_recursivesubdir(globs, dirents, i, j)); // recursive glob function returns 1 if it eventually matches
			}
			j++;
		}
	}
	printf("ft_recursivesubjoker return 0?\n");
	return (0);
}

int	ft_recursivejoker(t_globs *globs, char *dname, int i, int j)
{
	int		tempj;

	tempj = j;
	if (globs->gend[j] == '\0') // no globend means every end matches
		return (1); // this one is a match
	while (dname[i + j]) // while there are characters in filename 
	{
		if (dname[i + j] == globs->gend[j] || globs->gend[j] == '\0') // if the first character matches or there is no globend
		{
			if (globs->gend[j] == '\0') // no globend means every end matches
				return (1); // this one is a match
			if (dname[i + j + 1] == '\0') // no globend means every end matches
				return (1); // this one is a match
			while (dname[i + j] && globs->gend[j] && dname[i + j] == globs->gend[j]) //while the first character was a match but globend exists
				j++;
			if (ft_strchr("*/[", globs->gend[j])) // if we find a new glob
				return (ft_recursiveglob(globs, dname, i, j)); // recursive glob function returns 1 if it eventually matches
			if (dname[i + j] == '\0') // the whole filename matches
				return (1); // copy it over.
			else // we have no match and reset the globend counter.
				j = tempj;
		}
		i++;
	}
	return (0);
}

int	ft_parsejoker(t_globs *globs, char *dname, int i)
{
	int	j;

	j = 0;
	if (globs->gstart[0] != '.' && dname[0] == '.') // if there is a period mismatch
	{
		ft_printf("ft_parsejoker Periods don't match\n");
		return (0); // we don't want to parse this one.
	}
	while (dname[i]) // while there are characters in filename 
	{
		if (dname[i] == globs->gend[j] || globs->gend[0] == '\0') // if the first character matches or there is no globend
		{
			if (globs->gend[0] == '\0') // no globend means every end matches
			{
				printf("ft_parsejoker no characters after glob so this matches\n");
				return (1); // this one is a match
			}
			while (dname[i + j] && globs->gend[j] && dname[i + j] == globs->gend[j]) //while the first character was a match but globend exists
			{
				printf("ft_parsejoker fastmatch %c\n", dname[i + j]);
				j++;
			}
			if (dname[i + j] == '\0') // the whole filename matches
			{
				printf("ft_parsejoker whole filename matches\n");
				return (1); // copy it over.
			}
			if (ft_strchr("*?[", globs->gend[j])) // if we find a new glob
			{
				printf("ft_parsejoker recursive glob found\n");
				return (ft_recursiveglob(globs, dname, i, j)); // recursive glob function returns 1 if it eventually matches
			}
			else // we have no match and reset the globend counter.
			{
				i++;
				j = 0;
			}
		}
		else // no matching first character means we can move over a character and try to match from there.
			i++;
	}
	return (0); // no matches found.
}