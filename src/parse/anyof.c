/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   anyof.c                                         |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: houtworm <codam@houtworm.net>              //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/09/20 00:51:38 by houtworm     /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/09/21 10:19:27 by djonker      \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int		ft_nextsubanyof(t_globs *globs, int i, int j, int k)
{
	int	tempj;

	/*printf("ft_nextsubanyof starting with j: %d k: %d, dname: %c glob: %c\n", j, k, globs->tempsubdir[i][k], globs->subdir[i][j]);*/
	if (globs->subdir[i][j] == '\0') // no globend means every end matches
	{
		/*ft_printf("ft_nextsubanyof end of glob\n");*/
		return (1); // this one is a match
	}
	tempj = j;
	while (globs->tempsubdir[i][k] && globs->subdir[i][j]) // while there are characters in filename 
	{
		if (globs->tempsubdir[i][k] == globs->subdir[i][j])
		{
			while (globs->tempsubdir[i][k] && globs->subdir[i][j] && globs->tempsubdir[i][k] == globs->subdir[i][j]) //while the characters match we skip them
			{
				/*printf("ft_nextsubanyof fastmatch: %c, %c\n", globs->subdir[i][j], globs->tempsubdir[i][k]);*/
				j++;
				k++;
			}
			/*printf("ft_nextsubanyof fastmatch broken: %c, %c\n", globs->subdir[i][j], globs->tempsubdir[i][k]);*/
			if (globs->subdir[i][j] == '\0') // if the end matches too
			{
				if (globs->temptype == DT_DIR) // check if it is a directory
				{
					/*printf("ft_nextsubanyof glob matches %s will be replaced with /%s in subdir %d\n", globs->subdir[i], globs->tempsubdir[i], i);*/
					return (1); // this one is a match
				}
				else
				{
					if (globs->subdir[i + 1])
					{
						/*printf("ft_nextsubanyof %s is not a dir and we need to go deeper so no match\n", globs->tempsubdir[i]);*/
						return (0);
					}
					else
					{
						/*printf("ft_nextsubanyof %s matches but is not a dir but we are at our dept so match\n", globs->tempsubdir[i]);*/
						return (1);
					}
				}
			}
			else if (globs->subdir[i][j] && ft_strchr("*?[", globs->subdir[i][j])) // if we find a new glob
			{
				/*printf("ft_nextsubanyof found glob going into recursion\n");*/
				return (ft_nextsubglob(globs, i, j, k)); // recursive glob function returns 1 if it eventually matches
			}
			else
				j = tempj;
		}
		k++;
	}
	return (0);
}

int		ft_firstsubanyof(t_globs *globs, struct dirent *dirents, int i, int itar)
{
	int	ipos;

	ipos = 0;
	while (globs->subdir[i][ipos] != '*')
		ipos++;
	/*ipos++;*/
	if ((globs->subdir[i][0] == '.' && dirents->d_name[0] == '.') || (globs->subdir[i][0] != '.' && dirents->d_name[0] != '.')) // if first character of globstart is not a .
	{
		/*printf("ft_firstsubanyof periods match for %s\n", dirents->d_name);*/
		/*if (globs->subdir[i][j] == '\0' || dirents->d_name[j] == '\0') // the whole filename matches*/
		/*{*/
			/*printf("ft_recursivesubanyof just a * so %s is an easy match\n", dirents->d_name);*/
			/*globs->tempsubdir[i] = ft_strjoin("/", dirents->d_name);*/
			/*return (1); // copy it over.*/
		/*}*/
		while (dirents->d_name[ipos]) // while there are characters in filename 
		{
			if (globs->subdir[i][itar] == '\0') // the whole filename matches
			{
				/*printf("ft_firstsubanyof just a * so %s is an easy match\n", dirents->d_name);*/
				globs->tempsubdir[i] = ft_strjoin("/", dirents->d_name);
				return (1); // copy it over.
			}
			while (dirents->d_name[ipos] && globs->subdir[i][itar] && dirents->d_name[ipos] == globs->subdir[i][itar]) //while the characters match we skip them
			{
				/*printf("ft_firstsubanyof fastmatch: %c, %c\n", globs->subdir[i][itar], dirents->d_name[ipos]);*/
				itar++;
				ipos++;
			}
			/*printf("ft_firstsubanyof fastmatch broken: %c, %c\n", globs->subdir[i][itar], dirents->d_name[ipos]);*/
			if (globs->subdir[i][itar] == '\0') // if the end matches too
			{
				if (dirents->d_type == DT_DIR) // check if it is a directory
				{
					/*printf("ft_firstsubanyof glob matches %s will be replaced with /%s in subdir %d\n", globs->subdir[i], dirents->d_name, i);*/
					globs->tempsubdir[i] = ft_strjoin("/", dirents->d_name);
					return (1); // this one is a match
				}
				else
				{
					if (globs->subdir[i + 1])
					{
						/*printf("ft_firstsubanyof %s is not a dir and we need to go deeper so no match\n", dirents->d_name);*/
						return (0);
					}
					else
					{
						globs->tempsubdir[i] = ft_strjoin("/", dirents->d_name);
						/*printf("ft_firstsubanyof %s matches but is not a dir but we are at our dept so match\n", dirents->d_name);*/
						return (1);
					}
				}
			}
			else if (globs->subdir[i][itar] && ft_strchr("*?[", globs->subdir[i][itar])) // if we find a new glob
			{
				/*printf("ft_firstsubanyof found glob going into recursion\n");*/
				globs->tempsubdir[i] = ft_strjoin("/", dirents->d_name);
				globs->temptype = dirents->d_type;
				if (ft_nextsubglob(globs, i, itar, ipos)) // recursive glob function returns 1 if it eventually matches
				{
					if (dirents->d_type == DT_DIR) // check if it is a directory
					{
						/*printf("ft_firstsubanyof glob matches %s will be replaced with /%s in subdir %d\n", globs->subdir[i], dirents->d_name, i);*/
						globs->tempsubdir[i] = ft_strjoin("/", dirents->d_name);
						return (1); // this one is a match
					}
					else
					{
						if (globs->subdir[i + 1])
						{
							/*printf("ft_firstsubanyof %s is not a dir and we need to go deeper so no match\n", dirents->d_name);*/
							return (0);
						}
						else
						{
							globs->tempsubdir[i] = ft_strjoin("/", dirents->d_name);
							/*printf("ft_firstsubanyof %s matches but is not a dir but we are at our dept so match\n", dirents->d_name);*/
							return (1);
						}
					}
				}
				else
					return (0);
			}
			ipos++;
		}
	}
	/*printf("ft_firstsubanyof return 0?\n");*/
	return (0);
}

int	ft_nextanyof(t_globs *globs, char *dname, int i, int j)
{
	int		tempj;

	tempj = j;
	if (globs->gend[j] == '\0') // no globend means every end matches
	{
		/*ft_printf("ft_nextanyof end of glob\n");*/
		return (1); // this one is a match
	}
	while (dname[i + j]) // while there are characters in filename 
	{
		if (dname[i + j] == globs->gend[j]) // if the first character matches or there is no globend
		{
			/*if (dname[i + j] == '\0') // no globend means every end matches*/
				/*return (1); // this one is a match*/
			while (dname[i + j] && globs->gend[j] && dname[i + j] == globs->gend[j]) //while the first character was a match but globend exists
			{
				/*printf("ft_nextanyof fastmatch %c\n", dname[i + j]);*/
				j++;
			}
			/*printf("ft_nextanyof fastmatch break %c %c\n", dname[i + j], globs->gend[j]);*/
			if (globs->gend[j] && ft_strchr("*?[", globs->gend[j])) // if we find a new glob
			{
				/*printf("ft_nextanyof glob found going into recursion\n");*/
				return (ft_nextglob(globs, dname, i, j)); // recursive glob function returns 1 if it eventually matches
			}
			if (dname[i + j] == '\0') // the whole filename matches
			{
				/*printf("ft_nextwilcard reached end of dname\n");*/
				return (1); // copy it over.
			}
			else // we have no match and reset the globend counter.
			{
				/*printf("ft_nextanyof skipping one character\n");*/
				j = tempj;
			}
		}
		i++;
	}
	return (0);
}

int	ft_firstanyof(t_globs *globs, char *dname, int i)
{
	int	j;

	j = 0;
	if (globs->gstart[0] != '.' && dname[0] == '.') // if there is a period mismatch
	{
		/*ft_printf("ft_firstanyof Periods don't match\n");*/
		return (0); // we don't want to parse this one.
	}
	while (dname[i]) // while there are characters in filename 
	{
		if (dname[i] == globs->gend[j] || globs->gend[0] == '\0') // if the first character matches or there is no globend
		{
			if (globs->gend[0] == '\0') // no globend means every end matches
			{
				/*printf("ft_firstanyof no characters after glob so this matches\n");*/
				return (1); // this one is a match
			}
			while (dname[i + j] && globs->gend[j] && dname[i + j] == globs->gend[j]) //while the first character was a match but globend exists
			{
				/*printf("ft_firstanyof fastmatch %c\n", dname[i + j]);*/
				j++;
			}
			if (dname[i + j] == '\0' && globs->gend[j] == '\0') // the whole filename matches
			{
				/*printf("ft_firstanyof whole filename matches\n");*/
				return (1); // copy it over.
			}
			if (ft_strchr("*?[", globs->gend[j])) // if we find a new glob
			{
				/*printf("ft_firstanyof recursive glob found\n");*/
				return (ft_nextglob(globs, dname, i, j)); // recursive glob function returns 1 if it eventually matches
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
