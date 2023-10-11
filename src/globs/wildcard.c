/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   wildcard.c                                      |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: houtworm <codam@houtworm.net>              //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/08/27 08:14:23 by houtworm     /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/10/11 13:52:02 by djonker      \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int		ft_nextsubwildcard(t_globs *globs, int i, int j, int k)
{
	int	tempj;

	/*printf("ft_nextsubwildcard starting with j: %d k: %d, dname: %c glob: %c\n", j, k, globs->tempsubdir[i][k], globs->subdir[i][j]);*/
	while (globs->subdir[i][j] == '*')
		j++;
	if (globs->subdir[i][j] == '\0') // no globend means every end matches
	{
		/*printf("ft_nextsubwildcard end of glob\n");*/
		return (1); // this one is a match
	}
	/*printf("ft_nextsubwildcard after skip * with j: %d k: %d, dname: %c glob: %c\n", j, k, globs->tempsubdir[i][k], globs->subdir[i][j]);*/
	tempj = j;
	while (globs->tempsubdir[i][k] && globs->subdir[i][j]) // while there are characters in filename 
	{
		if (globs->tempsubdir[i][k] == globs->subdir[i][j])
		{
			while (globs->subdir[i][j] == '\\' || (globs->tempsubdir[i][k] && globs->subdir[i][j] && globs->tempsubdir[i][k] == globs->subdir[i][j])) //while the characters match we skip them
			{
				/*printf("ft_nextsubwildcard fastmatch: %c, %c\n", globs->subdir[i][j], globs->tempsubdir[i][k]);*/
				if (globs->subdir[i][j] == '\\')
					j++;
				else
				{
					j++;
					k++;
				}
			}
			/*printf("ft_nextsubwildcard fastmatch broken: %c, %c\n", globs->subdir[i][j], globs->tempsubdir[i][k]);*/
			if (globs->subdir[i][j] == '\0') // if the end matches too
			{
				if (globs->temptype == DT_DIR) // check if it is a directory
				{
					/*printf("ft_nextsubwildcard glob matches %s will be replaced with /%s in subdir %d\n", globs->subdir[i], globs->tempsubdir[i], i);*/
					return (1); // this one is a match
				}
				else
				{
					if (globs->subdir[i + 1])
					{
						/*printf("ft_nextsubwildcard %s is not a dir and we need to go deeper so no match\n", globs->tempsubdir[i]);*/
						return (0);
					}
					else
					{
						/*printf("ft_nextsubwildcard %s matches but is not a dir but we are at our dept so match\n", globs->tempsubdir[i]);*/
						return (1);
					}
				}
			}
			else if (globs->subdir[i][j] && ft_strchr("*?[", globs->subdir[i][j])) // if we find a new glob
			{
				/*printf("ft_nextsubwildcard found %c going into recursion\n", globs->subdir[i][j]);*/
				return (ft_nextsubglob(globs, i, j, k)); // recursive glob function returns 1 if it eventually matches
			}
			else
				j = tempj;
		}
		else if (globs->subdir[i][j] && ft_strchr("*?[", globs->subdir[i][j])) // if we find a new glob
		{
			/*printf("ft_nextsubwildcard found %c going into recursion\n", globs->subdir[i][j]);*/
			return (ft_nextsubglob(globs, i, j, k)); // recursive glob function returns 1 if it eventually matches
		}
		k++;
	}
	/*printf("ft_nextsubwildcard return 0 j: %d, k: %d\n", j, k);*/
	return (0);
}

int		ft_firstsubwildcard(t_globs *globs, struct dirent *dirents, int i, int itar)
{
	int	ipos;

	ipos = itar - 1;
	while (globs->subdir[i][itar] == '*')
		itar++;
	if ((globs->subdir[i][0] == '.' && dirents->d_name[0] == '.') || (globs->subdir[i][0] != '.' && dirents->d_name[0] != '.')) // if first character of globstart is not a .
	{
		/*printf("ft_firstsubwildcard periods match for %s\n", dirents->d_name);*/
		while (dirents->d_name[ipos]) // while there are characters in filename 
		{
			if (globs->subdir[i][itar] == '\0') // the whole filename matches
			{
				/*printf("ft_firstsubwildcard just a * so %s is an easy match\n", dirents->d_name);*/
				free(globs->tempsubdir[i]);
				globs->tempsubdir[i] = ft_strjoin("/", dirents->d_name);
				return (1); // copy it over.
			}
			while (globs->subdir[i][itar] == '\\' || (dirents->d_name[ipos] && globs->subdir[i][itar] && dirents->d_name[ipos] == globs->subdir[i][itar])) //while the characters match we skip them
			{
				/*printf("ft_firstsubwildcard fastmatch: %c, %c\n", globs->subdir[i][itar], dirents->d_name[ipos]);*/
				if (globs->subdir[i][itar] == '\\')
					itar++;
				else
				{
					itar++;
					ipos++;
				}
			}
			/*printf("ft_firstsubwildcard fastmatch broken: %c, %c j: %d, k: %d\n", globs->subdir[i][itar], dirents->d_name[ipos], itar, ipos);*/
			if (globs->subdir[i][itar] == '\0') // if the end matches too
			{
				if (dirents->d_type == DT_DIR) // check if it is a directory
				{
					/*printf("ft_firstsubwildcard glob matches %s will be replaced with /%s in subdir %d\n", globs->subdir[i], dirents->d_name, i);*/
					free(globs->tempsubdir[i]);
					globs->tempsubdir[i] = ft_strjoin("/", dirents->d_name);
					return (1); // this one is a match
				}
				else
				{
					if (globs->subdir[i + 1])
					{
						/*printf("ft_firstsubwildcard %s is not a dir and we need to go deeper so no match\n", dirents->d_name);*/
						return (0);
					}
					else
					{
						free(globs->tempsubdir[i]);
						globs->tempsubdir[i] = ft_strjoin("/", dirents->d_name);
						/*printf("ft_firstsubwildcard %s matches but is not a dir but we are at our dept so match\n", dirents->d_name);*/
						return (1);
					}
				}
			}
			else if (globs->subdir[i][itar] && ft_strchr("*?[", globs->subdir[i][itar])) // if we find a new glob
			{
				/*printf("ft_firstsubwildcard found glob going into recursion\n");*/
				free(globs->tempsubdir[i]);
				globs->tempsubdir[i] = ft_strjoin("/", dirents->d_name);
				globs->temptype = dirents->d_type;
				if (ft_nextsubglob(globs, i, itar, ipos + 1)) // recursive glob function returns 1 if it eventually matches
				{
					if (dirents->d_type == DT_DIR) // check if it is a directory
					{
						/*printf("ft_firstsubwildcard glob matches %s will be replaced with /%s in subdir %d\n", globs->subdir[i], dirents->d_name, i);*/
						free(globs->tempsubdir[i]);
						globs->tempsubdir[i] = ft_strjoin("/", dirents->d_name);
						return (1); // this one is a match
					}
					else
					{
						if (globs->subdir[i + 1])
						{
							/*printf("ft_firstsubwildcard %s is not a dir and we need to go deeper so no match\n", dirents->d_name);*/
							return (0);
						}
						else
						{
							free(globs->tempsubdir[i]);
							globs->tempsubdir[i] = ft_strjoin("/", dirents->d_name);
							/*printf("ft_firstsubwildcard %s matches but is not a dir but we are at our dept so match\n", dirents->d_name);*/
							return (1);
						}
					}
				}
				else if (globs->subdir[i][itar - 1] != '*' && globs->subdir[i][itar] == '?' && !globs->tempsubdir[i][ipos + 3] && !globs->subdir[i][itar + 1])
				{
					/*printf("target hit\n");*/
					return (0);
				}
				/*printf("dname[ipos + 2]: %c, subdir[i][itar]: %c\n", globs->tempsubdir[i][ipos + 3], globs->subdir[i][itar]);*/
			}
			ipos++;
		}
	}
	/*printf("ft_firstsubwildcard return 0?\n");*/
	return (0);
}

int	ft_nextwildcard(t_globs *globs, char *dname, int i, int j)
{
	int		tempj;
	int		tempi;

	while (globs->gend[j] == '*')
		j++;
	tempj = j;
	tempi = i;
	if (globs->gend[j] == '\0') // no globend means every end matches
	{
		/*printf("ft_nextwildcard end of glob\n");*/
		return (1); // this one is a match
	}
	while (dname[i]) // while there are characters in filename 
	{
		if (globs->gend[j] == '\\' || dname[i] == globs->gend[j]) // if the first character matches or there is no globend
		{
			while (globs->gend[j] == '\\' || (dname[i] && globs->gend[j] && dname[i] == globs->gend[j])) //while the first character was a match but globend exists
			{
				if (globs->gend[j] == '\\')
					j++;
				else
				{
					/*printf("ft_nextwildcard fastmatch %c\n", dname[i]);*/
					j++;
					i++;
				}
			}
			/*printf("ft_nextwildcard fastmatch break %c %c\n", dname[i], globs->gend[j]);*/
			if (globs->gend[j] && ft_strchr("*?[", globs->gend[j])) // if we find a new glob
			{
				/*printf("ft_nextwildcard glob found going into recursion\n");*/
				return (ft_nextglob(globs, dname, i, j)); // recursive glob function returns 1 if it eventually matches
			}
			if (dname[i] == '\0') // the whole filename matches
			{
				/*printf("ft_nextwilcard reached end of dname\n");*/
				return (1); // copy it over.
			}
			else // we have no match and reset the globend counter.
			{
				/*printf("ft_nextwildcard skipping one character\n");*/
				j = tempj;
			}
		}
		if (globs->gend[j] && ft_strchr("*?[", globs->gend[j])) // if we find a new glob
		{
			/*printf("ft_nextwildcard glob found going into recursion\n");*/
			return (ft_nextglob(globs, dname, i, j)); // recursive glob function returns 1 if it eventually matches
		}
		tempi++;
		i = tempi;
	}
	return (0);
}

int	ft_firstwildcard(t_globs *globs, char *dname, int i)
{
	int	j;
	int	temp;
	int	ret;

	temp = i;
	j = 0;
	if (globs->gstart[0] != '.' && dname[0] == '.') // if there is a period mismatch
	{
		/*printf("ft_firstwildcard Periods don't match\n");*/
		return (0); // we don't want to parse this one.
	}
	while (globs->gend[j] == '*')
		j++;
	if (globs->gend[j] == '\0' && dname[i] == '\0')
		return (1);
	while (dname[i]) // while there are characters in filename 
	{
		while (globs->gend[j] == '*')
			j++;
		if (dname[i] == globs->gend[j] || globs->gend[0] == '\0') // if the first character matches or there is no globend
		{
			if (globs->gend[0] == '\0') // no globend means every end matches
			{
				/*printf("ft_firstwildcard no characters after glob so this matches\n");*/
				return (1); // this one is a match
			}
			while (globs->gend[j] == '\\' || (dname[i] && globs->gend[j] && dname[i] == globs->gend[j])) //while the first character was a match but globend exists
			{
				if (globs->gend[j] == '\\')
					j++;
				else
				{
					/*printf("ft_firstwildcard fastmatch %c\n", dname[i]);*/
					j++;
					i++;
				}
			}
			if (dname[i] == '\0' && globs->gend[j] == '\0') // the whole filename matches
			{
				/*printf("ft_firstwildcard whole filename matches\n");*/
				return (1); // copy it over.
			}
			if (ft_strchr("*?[", globs->gend[j])) // if we find a new glob
			{
				/*printf("ft_firstwildcard recursive glob found\n");*/
				ret = ft_nextglob(globs, dname, i, j); // recursive glob function returns 1 if it eventually matches
				if (ret == 1)
					return (ret);
				i++;
				j = 0;
			}
			else // we have no match and reset the globend counter.
			{
				i++;
				j = 0;
			}
		}
		else if (ft_strchr("*?[", globs->gend[j])) // if we find a new glob
		{
			/*printf("ft_firstwildcard recursive glob found\n");*/
			ret = ft_nextglob(globs, dname, i, j); // recursive glob function returns 1 if it eventually matches
			if (ret == 1)
				return (ret);
			temp++;
			i = temp;
		}
		else // no matching first character means we can move over a character and try to match from there.
		{
			temp++;
			i = temp;
		}
	}
	/*printf("return 0\n");*/
	return (0); // no matches found.
}
