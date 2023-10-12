/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   joker.c                                         |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: houtworm <codam@houtworm.net>              //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/09/20 00:51:17 by houtworm     /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/10/12 20:59:42 by houtworm     \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int		ft_nextsubjoker(t_globs *globs, int si, int ri, int gi)
{
	/*printf("ft_nextsubjoker starting with j: %d k: %d, dname: %c glob: %c\n", gi, ri, globs->tempsubdir[si][ri], globs->subdir[si][gi]);*/
	while (globs->subdir[si][gi] == '\\' || (globs->tempsubdir[si][ri] && globs->subdir[si][gi] && globs->tempsubdir[si][ri] == globs->subdir[si][gi])) //while the characters match we skip them
	{
		if (globs->subdir[si][gi] == '\\')
			gi++;
		else
		{
			/*printf("ft_nextsubjoker fastmatch: %c, %c\n", globs->subdir[si][gi], globs->tempsubdir[si][ri]);*/
			gi++;
			ri++;
		}
	}
	/*printf("ft_nextsubjoker fastmatch broken: %c, %c\n", globs->subdir[si][gi], globs->tempsubdir[si][ri]);*/
	if (globs->subdir[si][gi] == '\0' && globs->tempsubdir[si][ri] == '\0') // if the end matches too
	{
		if (globs->temptype == DT_DIR) // check if it is a directory
		{
			/*printf("ft_nextsubjoker glob matches %s will be replaced with /%s in subdir %d\n", globs->subdir[si], globs->tempsubdir[si], si);*/
			return (1); // this one is a match
		}
		else
		{
			if (globs->subdir[si + 1])
			{
				/*printf("ft_nextsubjoker %s is not a dir and we need to go deeper so no match\n", globs->tempsubdir[si]);*/
				return (0);
			}
			else
			{
				/*printf("ft_nextsubjoker %s matches but is not a dir but we are at our dept so match\n", globs->tempsubdir[si]);*/
				return (1);
			}
		}
	}
	if (globs->subdir[si][gi - 1] != '\\' && globs->subdir[si][gi] == '*' && globs->tempsubdir[si][ri] == '\0') // the whole filename matches
	{
		/*printf("ft_nextjoker ends with *\n");*/
		return (ft_nextsubglob(globs, si, ri, gi));
	}
	if (globs->subdir[si][gi] == '\0' || globs->tempsubdir[si][ri] == '\0') // mismatch
	{
		/*printf("mismatch\n");*/
		return (0);
	}
	else if (globs->subdir[si][gi - 1] != '\\' && globs->subdir[si][gi] && ft_strchr("*?[", globs->subdir[si][gi])) // if we find a new glob
	{
		/*printf("ft_nextsubjoker found glob going into recursion\n");*/
		return (ft_nextsubglob(globs, si, ri, gi)); // recursive glob function returns 1 if it eventually matches
	}
	return (0);
}

int		ft_firstsubjoker(t_globs *globs, struct dirent *dirents, int si, int gi)
{
	int		ri;

	ri = gi - 1;
	if ((globs->subdir[si][0] == '.' && dirents->d_name[0] == '.') || (globs->subdir[si][0] != '.' && dirents->d_name[0] != '.')) // if first character of globstart is not a .
	{
		while (globs->subdir[si][gi] == '\\' || (dirents->d_name[ri] && globs->subdir[si][gi] && dirents->d_name[ri] == globs->subdir[si][gi])) //while the characters match we skip them
		{
			if (globs->subdir[si][gi] == '\\')
				gi++;
			else
			{
				/*printf("ft_firstsubjoker fastmatch: %c, %c\n", globs->subdir[si][gi], dirents->d_name[ri]);*/
				gi++;
			}
		}
		/*printf("ft_firstsubjoker fastmatch broken: %c, %c\n", globs->subdir[si][gi], dirents->d_name[ri]);*/
		if (globs->subdir[si][gi] == '\0' && dirents->d_name[ri] == '\0') // if the end matches too
		{
			if (dirents->d_type == DT_DIR) // check if it is a directory
			{
				/*printf("ft_firstsubjoker glob matches %s will be replaced with /%s in subdir %d\n", globs->subdir[si], dirents->d_name, si);*/
				free(globs->tempsubdir[si]);
				globs->tempsubdir[si] = ft_strjoin("/", dirents->d_name);
				return (1); // this one is a match
			}
			else
			{
				if (globs->subdir[si + 1])
				{
					/*printf("ft_firstsubjoker %s is not a dir and we need to go deeper so no match\n", dirents->d_name);*/
					return (0);
				}
				else
				{
					free(globs->tempsubdir[si]);
					globs->tempsubdir[si] = ft_strjoin("/", dirents->d_name);
					/*printf("ft_firstsubjoker %s matches but is not a dir but we are at our dept so match\n", dirents->d_name);*/
					return (1);
				}
			}
		}
		if (globs->subdir[si][gi] == '\0' && dirents->d_name[ri] == '\0') // if both are at their end
		{
			/*printf("return 1\n");*/
			return (1);
		}
		if (globs->subdir[si][gi] == '\0' || dirents->d_name[gi - 1] == '\0') // if there is a mismatch
		{
			/*printf("ft_firstsubjoker return 0\n");*/
			return (0);
		}
		if (globs->subdir[si][gi] && ft_strchr("*?[", globs->subdir[si][gi])) // if we find a new glob
		{
			/*printf("ft_firstsubjoker found glob going into recursion\n");*/
			free(globs->tempsubdir[si]);
			globs->tempsubdir[si] = ft_strjoin("/", dirents->d_name);
			globs->temptype = dirents->d_type;
			if (ft_nextsubglob(globs, si, gi, gi)) // recursive glob function returns 1 if it eventually matches
			{
				if (dirents->d_type == DT_DIR) // check if it is a directory
				{
					/*printf("ft_firstsubjoker glob matches %s will be replaced with /%s in subdir %d\n", globs->subdir[si], dirents->d_name, si);*/
					free(globs->tempsubdir[si]);
					globs->tempsubdir[si] = ft_strjoin("/", dirents->d_name);
					return (1); // this one is a match
				}
				else
				{
					if (globs->subdir[si + 1])
					{
						/*printf("ft_firstsubjoker %s is not a dir and we need to go deeper so no match\n", dirents->d_name);*/
						return (0);
					}
					else
					{
						free(globs->tempsubdir[si]);
						globs->tempsubdir[si] = ft_strjoin("/", dirents->d_name);
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

int	ft_nextjoker(t_globs *globs, char *dname, int ri, int gi)
{
	while (globs->gend[gi] == '\\' || (dname[ri] && globs->gend[gi] && dname[ri] == globs->gend[gi])) //while the characters match
	{
		if (globs->gend[gi] == '\\')
		{
			/*printf("ft_nextjoker found a \\ in gend\n");*/
			gi++;
		}
		else
		{
			/*printf("ft_nextjoker fastmatch %c\n", dname[ri]);*/
			gi++;
			ri++;
		}
	}
	/*printf("ft_nextjoker fastmatch break %c %c\n", dname[ri], globs->gend[gi]);*/
	if (dname[ri] && globs->gend[gi] && ft_strchr("*?[", globs->gend[gi]) && globs->gend[gi - 1] != '\\') // if we find a new glob
	{
		/*printf("ft_nextjoker glob found going into recursion\n");*/
		return (ft_nextglob(globs, dname, ri, gi)); // recursive glob function returns 1 if it eventually matches
	}
	if (globs->gend[gi] == '\0' && dname[ri] == '\0') // the whole filename matches
	{
		/*printf("ft_nextjoker reached end of dname\n");*/
		return (1); // copy it over.
	}
	if (globs->gend[gi - 1] != '\\' && globs->gend[gi] == '*' && dname[ri] == '\0') // the whole filename matches
	{
		/*printf("ft_nextjoker ends with *\n");*/
		return (ft_nextglob(globs, dname, ri, gi)); //fuck this.
	}
	if (globs->gend[gi] == '\0' || dname[ri] == '\0') // the whole filename matches
	{
		/*printf("ft_nextjoker mismatch in end\n");*/
		return (0); //fuck this.
	}
	return (0);
}

int	ft_firstjoker(t_globs *globs, char *dname, int ri)
{
	int	gi;

	gi = 0;
	/*printf("ft_firstjoker starting with dname: %c and gend: %c\n", dname[ri], globs->gend[gi]);*/
	if (globs->gstart[0] != '.' && dname[0] == '.') // if there is a period mismatch
	{
		return (0); // we don't want to parse this one.
	}
	while (globs->gend[gi] == '\\' || (dname[ri] && globs->gend[gi] && dname[ri] == globs->gend[gi])) //while the first character was a match but globend exists
	{
		if (globs->gend[gi] == '\\')
		{
			/*printf("ft_firstwildcard found a \\\n");*/
			gi++;
		}
		else
		{
			/*printf("ft_firstjoker fastmatch %c\n", dname[ri]);*/
			gi++;
			ri++;
		}
	}
	if (dname[ri] == '\0' && globs->gend[gi] == '\0') // the whole filename matches
	{
		/*printf("ft_firstjoker whole filename matches\n");*/
		return (1); // copy it over.
	}
	if (dname[ri] == '\0' || globs->gend[gi] == '\0') // mismatch
	{
		return (0);
	}
	if (ft_strchr("*?[", globs->gend[gi])) // if we find a new glob
	{
		/*printf("ft_firstjoker recursive glob found\n");*/
		return (ft_nextglob(globs, dname, ri, gi)); // recursive glob function returns 1 if it eventually matches
	}
	return (0); // no matches found.
}
