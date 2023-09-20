/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   wildcard.c                                      |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: houtworm <codam@houtworm.net>              //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/08/27 08:14:23 by houtworm     /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/09/21 00:43:51 by djonker      \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int		ft_recursivesubwildcard(t_globs *globs, struct dirent *dirents, int i, int j)
{
	if ((globs->subdir[i][0] == '.' && dirents->d_name[0] == '.') || (globs->subdir[i][0] != '.' && dirents->d_name[0] != '.')) // if first character of globstart is not a .
	{
		printf("ft_recursivesubwildcard periods match for %s\n", dirents->d_name);
		if (globs->subdir[i][j] == '\0' || dirents->d_name[j] == '\0') // the whole filename matches
		{
			printf("ft_recursivesubwildcard just a * so %s is an easy match\n", dirents->d_name);
			globs->tempsubdir[i] = ft_strjoin("/", dirents->d_name);
			return (1); // copy it over.
		}
		while (dirents->d_name[j]) // while there are characters in filename 
		{
			while (dirents->d_name[j] && globs->subdir[i][j + 1] && dirents->d_name[j] == globs->subdir[i][j + 1]) //while the characters match we skip them
			{
				printf("ft_recursivesubwildcard fastmatch: %c, %c\n", globs->subdir[i][j + 1], dirents->d_name[j]);
				j++;
			}
			printf("ft_recursivesubwildcard fastmatch broken: %c, %c\n", globs->subdir[i][j + 1], dirents->d_name[j]);
			if (globs->subdir[i][j + 1] == '\0') // if the end matches too
			{
				if (dirents->d_type == DT_DIR) // check if it is a directory
				{
					printf("ft_recursivesubwildcard glob matches %s will be replaced with /%s in subdir %d\n", globs->subdir[i], dirents->d_name, i);
					globs->tempsubdir[i] = ft_strjoin("/", dirents->d_name);
					return (1); // this one is a match
					// I think we should branch out here, match all the following subdirs....
				}
				else
				{
					if (globs->subdir[i + 1])
					{
						printf("ft_recursivesubwildcard %s is not a dir and we need to go deeper so no match\n", dirents->d_name);
						return (0);
					}
					else
					{
						globs->tempsubdir[i] = ft_strjoin("/", dirents->d_name);
						printf("ft_recursivesubwildcard %s matches but is not a dir but we are at our dept so match\n", dirents->d_name);
						return (1);
					}
				}
			}
			else if (ft_strchr("*?[", globs->subdir[i][j + 1])) // if we find a new glob
			{
				printf("ft_recursivesubwildcard found glob going into recursion\n");
				globs->tempsubdir[i] = ft_strjoin("/", dirents->d_name);
				return (ft_recursivesubdir(globs, dirents, i, j)); // recursive glob function returns 1 if it eventually matches
			}
			/*else*/
				/*return (0);*/
			j++;
		}
	}
	printf("ft_recursivesubwildcard return 0?\n");
	return (0);
}

int	ft_recursivewildcard(t_globs *globs, char *dname, int i, int j)
{
	int		tempj;

	tempj = j;
	if (globs->gend[j] == '\0') // no globend means every end matches
		return (1); // this one is a match
	while (dname[i + j]) // while there are characters in filename 
	{
		if (dname[i + j] == globs->gend[j]) // if the first character matches or there is no globend
		{
			/*if (dname[i + j] == '\0') // no globend means every end matches*/
				/*return (1); // this one is a match*/
			while (dname[i + j] && globs->gend[j] && dname[i + j] == globs->gend[j]) //while the first character was a match but globend exists
				j++;
			if (ft_strchr("*?[", globs->gend[j])) // if we find a new glob
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

int	ft_parsewildcard(t_globs *globs, char *dname, int i)
{
	int	j;

	j = 0;
	if (globs->gstart[0] != '.' && dname[0] == '.') // if there is a period mismatch
	{
		ft_printf("ft_parsewildcard Periods don't match\n");
		return (0); // we don't want to parse this one.
	}
	while (dname[i]) // while there are characters in filename 
	{
		if (dname[i] == globs->gend[j] || globs->gend[0] == '\0') // if the first character matches or there is no globend
		{
			if (globs->gend[0] == '\0') // no globend means every end matches
			{
				printf("ft_parsewildcard no characters after glob so this matches\n");
				return (1); // this one is a match
			}
			while (dname[i + j] && globs->gend[j] && dname[i + j] == globs->gend[j]) //while the first character was a match but globend exists
			{
				printf("ft_parsewildcard fastmatch %c\n", dname[i + j]);
				j++;
			}
			printf("loop %s %c %s %c\n", dname, dname[i + j], globs->gend, globs->gend[j]);
			if (dname[i + j] == '\0' && globs->gend[j] == '\0') // the whole filename matches
			{
				printf("ft_parsewildcard whole filename matches\n");
				return (1); // copy it over.
			}
			if (ft_strchr("*?[", globs->gend[j])) // if we find a new glob
			{
				printf("ft_parsewildcard recursive glob found\n");
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
