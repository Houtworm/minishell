/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   joker.c                                         |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: houtworm <codam@houtworm.net>              //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/09/20 00:51:17 by houtworm     /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/09/30 00:16:05 by houtworm     \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int		ft_nextsubjoker(t_globs *globs, int i, int j, int k)
{
	/*printf("ft_nextsubjoker starting with j: %d k: %d, dname: %c glob: %c\n", j, k, globs->tempsubdir[i][k], globs->subdir[i][j]);*/
	while (globs->tempsubdir[i][k] && globs->subdir[i][j] && globs->tempsubdir[i][k] == globs->subdir[i][j]) //while the characters match we skip them
	{
		/*printf("ft_nextsubjoker fastmatch: %c, %c\n", globs->subdir[i][j], globs->tempsubdir[i][k]);*/
		j++;
		k++;
	}
	/*printf("ft_nextsubjoker fastmatch broken: %c, %c\n", globs->subdir[i][j], globs->tempsubdir[i][k]);*/
	if (globs->subdir[i][j] == '\0' && globs->tempsubdir[i][k] == '\0') // if the end matches too
	{
		if (globs->temptype == DT_DIR) // check if it is a directory
		{
			/*printf("ft_nextsubjoker glob matches %s will be replaced with /%s in subdir %d\n", globs->subdir[i], globs->tempsubdir[i], i);*/
			return (1); // this one is a match
		}
		else
		{
			if (globs->subdir[i + 1])
			{
				/*printf("ft_nextsubjoker %s is not a dir and we need to go deeper so no match\n", globs->tempsubdir[i]);*/
				return (0);
			}
			else
			{
				/*printf("ft_nextsubjoker %s matches but is not a dir but we are at our dept so match\n", globs->tempsubdir[i]);*/
				return (1);
			}
		}
	}
	if (globs->subdir[i][j] == '\0' || globs->tempsubdir[i][k] == '\0') // mismatch
	{
		return (0);
	}
	else if (globs->subdir[i][j] && ft_strchr("*?[", globs->subdir[i][j])) // if we find a new glob
	{
		/*printf("ft_nextsubjoker found glob going into recursion\n");*/
		return (ft_nextsubglob(globs, i, j, k)); // recursive glob function returns 1 if it eventually matches
	}
	return (0);
}

int		ft_firstsubjoker(t_globs *globs, struct dirent *dirents, int i, int itar)
{
	if ((globs->subdir[i][0] == '.' && dirents->d_name[0] == '.') || (globs->subdir[i][0] != '.' && dirents->d_name[0] != '.')) // if first character of globstart is not a .
	{
		while (dirents->d_name[itar] && globs->subdir[i][itar] && dirents->d_name[itar] == globs->subdir[i][itar]) //while the characters match we skip them
		{
			/*printf("ft_firstsubjoker fastmatch: %c, %c\n", globs->subdir[i][itar], dirents->d_name[itar]);*/
			itar++;
		}
		/*printf("ft_firstsubjoker fastmatch broken: %c, %c\n", globs->subdir[i][itar], dirents->d_name[itar - 1]);*/
		if (globs->subdir[i][itar] == '\0' && dirents->d_name[itar] == '\0') // if the end matches too
		{
			if (dirents->d_type == DT_DIR) // check if it is a directory
			{
				/*printf("ft_firstsubjoker glob matches %s will be replaced with /%s in subdir %d\n", globs->subdir[i], dirents->d_name, i);*/
				globs->tempsubdir[i] = ft_strjoin("/", dirents->d_name);
				return (1); // this one is a match
			}
			else
			{
				if (globs->subdir[i + 1])
				{
					/*printf("ft_firstsubjoker %s is not a dir and we need to go deeper so no match\n", dirents->d_name);*/
					return (0);
				}
				else
				{
					globs->tempsubdir[i] = ft_strjoin("/", dirents->d_name);
					/*printf("ft_firstsubjoker %s matches but is not a dir but we are at our dept so match\n", dirents->d_name);*/
					return (1);
				}
			}
		}
		if (globs->subdir[i][itar] == '\0' && dirents->d_name[itar - 1] == '\0') // if both are at their end
		{
			/*printf("return 1\n");*/
			return (1);
		}
		if (globs->subdir[i][itar] == '\0' || dirents->d_name[itar - 1] == '\0') // if there is a mismatch
		{
			/*printf("return 0\n");*/
			return (0);
		}
		if (globs->subdir[i][itar] && ft_strchr("*?[", globs->subdir[i][itar])) // if we find a new glob
		{
			/*printf("ft_firstsubjoker found glob going into recursion\n");*/
			globs->tempsubdir[i] = ft_strjoin("/", dirents->d_name);
			globs->temptype = dirents->d_type;
			if (ft_nextsubglob(globs, i, itar, itar)) // recursive glob function returns 1 if it eventually matches
			{
				if (dirents->d_type == DT_DIR) // check if it is a directory
				{
					/*printf("ft_firstsubjoker glob matches %s will be replaced with /%s in subdir %d\n", globs->subdir[i], dirents->d_name, i);*/
					globs->tempsubdir[i] = ft_strjoin("/", dirents->d_name);
					return (1); // this one is a match
				}
				else
				{
					if (globs->subdir[i + 1])
					{
						/*printf("ft_firstsubjoker %s is not a dir and we need to go deeper so no match\n", dirents->d_name);*/
						return (0);
					}
					else
					{
						globs->tempsubdir[i] = ft_strjoin("/", dirents->d_name);
						/*printf("ft_firstsubjoker %s matches but is not a dir but we are at our dept so match\n", dirents->d_name);*/
						return (1);
					}
				}
			}
			else
			{
				/*printf("return 0 at else\n");*/
				return (0);
			}
		}
	}
	/*printf("ft_firstsubjoker return 0?\n");*/
	return (0);
}

int	ft_nextjoker(t_globs *globs, char *dname, int i, int j)
{
	while (dname[i] && globs->gend[j] && dname[i] == globs->gend[j]) //while the characters match
	{
		/*printf("ft_nextjoker fastmatch %c\n", dname[i + j]);*/
		j++;
		i++;
	}
	/*printf("ft_nextjoker fastmatch break %c %c\n", dname[i], globs->gend[j]);*/
	if (dname[i] && globs->gend[j] && ft_strchr("*?[", globs->gend[j])) // if we find a new glob
	{
		/*printf("ft_nextjoker glob found going into recursion\n");*/
		return (ft_nextglob(globs, dname, i, j)); // recursive glob function returns 1 if it eventually matches
	}
	if (globs->gend[j] == '\0' && dname[i] == '\0') // the whole filename matches
	{
		/*printf("ft_nextjoker reached end of dname\n");*/
		return (1); // copy it over.
	}
	if (globs->gend[j] == '\0' || dname[i] == '\0') // the whole filename matches
	{
		/*printf("ft_nextjoker mismatch in end\n");*/
		return (0); //fuck this.
	}
	return (0);
}

int	ft_firstjoker(t_globs *globs, char *dname, int i)
{
	int	j;

	j = 0;
	/*printf("ft_firstjoker starting with dname: %c and gend: %c\n", dname[i + j], globs->gend[j]);*/
	if (globs->gstart[0] != '.' && dname[0] == '.') // if there is a period mismatch
	{
		return (0); // we don't want to parse this one.
	}
	while (dname[i] && globs->gend[j] && dname[i] == globs->gend[j]) //while the first character was a match but globend exists
	{
		/*printf("ft_firstjoker fastmatch %c\n", dname[i]);*/
		j++;
		i++;
	}
	if (dname[i] == '\0' && globs->gend[j] == '\0') // the whole filename matches
	{
		/*printf("ft_firstjoker whole filename matches\n");*/
		return (1); // copy it over.
	}
	if (dname[i] == '\0' || globs->gend[j] == '\0') // mismatch
	{
		return (0);
	}
	if (ft_strchr("*?[", globs->gend[j])) // if we find a new glob
	{
		/*printf("ft_firstjoker recursive glob found\n");*/
		return (ft_nextglob(globs, dname, i, j)); // recursive glob function returns 1 if it eventually matches
	}
	return (0); // no matches found.
}
