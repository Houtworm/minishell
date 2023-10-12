/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   wildcard.c                                      |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: houtworm <codam@houtworm.net>              //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/08/27 08:14:23 by houtworm     /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/10/12 18:14:26 by houtworm     \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int		ft_nextsubwildcard(t_globs *globs, int si, int gi, int ri)
{
	int	ti;

	/*printf("ft_nextsubwildcard starting with j: %d k: %d, dname: %c glob: %c\n", gi, ri, globs->tempsubdir[si][ri], globs->subdir[si][gi]);*/
	while (globs->subdir[si][gi] == '*')
		gi++;
	if (globs->subdir[si][gi] == '\0') // no globend means every end matches
	{
		/*printf("ft_nextsubwildcard end of glob\n");*/
		return (1); // this one is a match
	}
	/*printf("ft_nextsubwildcard after skip * with gi: %d ri: %d, dname: %c glob: %c\n", gi, ri, globs->tempsubdir[si][ri], globs->subdir[si][gi]);*/
	ti = gi;
	while (globs->tempsubdir[si][ri] && globs->subdir[si][gi]) // while there are characters in filename 
	{
		if (globs->tempsubdir[si][ri] == globs->subdir[si][gi])
		{
			while (globs->subdir[si][gi] == '\\' || (globs->tempsubdir[si][ri] && globs->subdir[si][gi] && globs->tempsubdir[si][ri] == globs->subdir[si][gi])) //while the characters match we skip them
			{
				if (globs->subdir[si][gi] == '\\')
					gi++;
				else
				{
					/*printf("ft_nextsubwildcard fastmatch: %c, %c\n", globs->subdir[si][gi], globs->tempsubdir[si][ri]);*/
					gi++;
					ri++;
				}
			}
			/*printf("ft_nextsubwildcard fastmatch broken: %c, %c\n", globs->subdir[si][gi], globs->tempsubdir[si][ri]);*/
			if (globs->subdir[si][gi] == '\0') // if the end matches too
			{
				if (globs->temptype == DT_DIR) // check if it is a directory
				{
					/*printf("ft_nextsubwildcard glob matches %s will be replaced with /%s in subdir %d\n", globs->subdir[si], globs->tempsubdir[si], si);*/
					return (1); // this one is a match
				}
				else
				{
					if (globs->subdir[si + 1])
					{
						/*printf("ft_nextsubwildcard %s is not a dir and we need to go deeper so no match\n", globs->tempsubdir[si]);*/
						return (0);
					}
					else
					{
						/*printf("ft_nextsubwildcard %s matches but is not a dir but we are at our dept so match\n", globs->tempsubdir[si]);*/
						return (1);
					}
				}
			}
			else if (globs->subdir[si][gi - 1] != '\\' && globs->subdir[si][gi] && ft_strchr("*?[", globs->subdir[si][gi])) // if we find a new glob
			{
				/*printf("ft_nextsubwildcard found %c going into recursion\n", globs->subdir[si][gi]);*/
				return (ft_nextsubglob(globs, si, gi, ri)); // recursive glob function returns 1 if it eventually matches
			}
			else
				gi = ti;
		}
		else if (globs->subdir[si][gi - 1] != '\\' && globs->subdir[si][gi] && ft_strchr("*?[", globs->subdir[si][gi])) // if we find a new glob
		{
			/*printf("ft_nextsubwildcard found %c going into recursion\n", globs->subdir[si][gi]);*/
			return (ft_nextsubglob(globs, si, gi, ri)); // recursive glob function returns 1 if it eventually matches
		}
		ri++;
	}
	/*printf("ft_nextsubwildcard return 0 gi: %d, ri: %d\n", gi, ri);*/
	return (0);
}

int		ft_firstsubwildcard(t_globs *globs, struct dirent *dirents, int si, int gi)
{
	int	ri;

	ri = gi - 1;
	while (globs->subdir[si][gi] == '*')
		gi++;
	if ((globs->subdir[si][0] == '.' && dirents->d_name[0] == '.') || (globs->subdir[si][0] != '.' && dirents->d_name[0] != '.')) // if first character of globstart is not a .
	{
		/*printf("ft_firstsubwildcard periods match for %s\n", dirents->d_name);*/
		while (dirents->d_name[ri]) // while there are characters in filename 
		{
			if (globs->subdir[si][gi] == '\0') // the whole filename matches
			{
				/*printf("ft_firstsubwildcard just a * so %s is an easy match\n", dirents->d_name);*/
				free(globs->tempsubdir[si]);
				globs->tempsubdir[si] = ft_strjoin("/", dirents->d_name);
				return (1); // copy it over.
			}
			while (globs->subdir[si][gi] == '\\' || (dirents->d_name[ri] && globs->subdir[si][gi] && dirents->d_name[ri] == globs->subdir[si][gi])) //while the characters match we skip them
			{
				/*printf("ft_firstsubwildcard fastmatch: %c, %c\n", globs->subdir[si][gi], dirents->d_name[ri]);*/
				if (globs->subdir[si][gi] == '\\')
					gi++;
				else
				{
					gi++;
					ri++;
				}
			}
			/*printf("ft_firstsubwildcard fastmatch broken: %c, %c j: %d, k: %d\n", globs->subdir[si][gi], dirents->d_name[ri], gi, ri);*/
			if (globs->subdir[si][gi] == '\0') // if the end matches too
			{
				if (dirents->d_type == DT_DIR) // check if it is a directory
				{
					/*printf("ft_firstsubwildcard glob matches %s will be replaced with /%s in subdir %d\n", globs->subdir[si], dirents->d_name, si);*/
					free(globs->tempsubdir[si]);
					globs->tempsubdir[si] = ft_strjoin("/", dirents->d_name);
					return (1); // this one is a match
				}
				else
				{
					if (globs->subdir[si + 1])
					{
						/*printf("ft_firstsubwildcard %s is not a dir and we need to go deeper so no match\n", dirents->d_name);*/
						return (0);
					}
					else
					{
						free(globs->tempsubdir[si]);
						globs->tempsubdir[si] = ft_strjoin("/", dirents->d_name);
						/*printf("ft_firstsubwildcard %s matches but is not a dir but we are at our dept so match\n", dirents->d_name);*/
						return (1);
					}
				}
			}
			else if (globs->subdir[si][gi] && ft_strchr("*?[", globs->subdir[si][gi])) // if we find a new glob
			{
				if (gi > 0 && globs->subdir[si][gi - 1] == '\\')
				{
					/*printf("skipping this not glob\n");*/
				}
				else
				{
					/*printf("ft_firstsubwildcard found glob going into recursion\n");*/
					free(globs->tempsubdir[si]);
					globs->tempsubdir[si] = ft_strjoin("/", dirents->d_name);
					globs->temptype = dirents->d_type;
					if (ft_nextsubglob(globs, si, gi, ri + 1)) // recursive glob function returns 1 if it eventually matches
					{
						if (dirents->d_type == DT_DIR) // check if it is a directory
						{
							/*printf("ft_firstsubwildcard glob matches %s will be replaced with /%s in subdir %d\n", globs->subdir[si], dirents->d_name, si);*/
							free(globs->tempsubdir[si]);
							globs->tempsubdir[si] = ft_strjoin("/", dirents->d_name);
							return (1); // this one is a match
						}
						else
						{
							if (globs->subdir[si + 1])
							{
								/*printf("ft_firstsubwildcard %s is not a dir and we need to go deeper so no match\n", dirents->d_name);*/
								return (0);
							}
							else
							{
								free(globs->tempsubdir[si]);
								globs->tempsubdir[si] = ft_strjoin("/", dirents->d_name);
								/*printf("ft_firstsubwildcard %s matches but is not a dir but we are at our dept so match\n", dirents->d_name);*/
								return (1);
							}
						}
					}
					else if (globs->subdir[si][gi - 1] != '*' && globs->subdir[si][gi] == '?' && !globs->tempsubdir[si][ri + 3] && !globs->subdir[si][gi + 1])
					{
						/*printf("target hit\n");*/
						return (0);
					}
				}
				/*printf("dname[ri + 2]: %c, subdir[si][gi]: %c\n", globs->tempsubdir[si][ri + 3], globs->subdir[si][gi]);*/
			}
			ri++;
		}
	}
	/*printf("ft_firstsubwildcard return 0?\n");*/
	return (0);
}

int	ft_nextwildcard(t_globs *globs, char *dname, int ri, int gi)
{
	int		tempj;
	int		tempi;

	while (globs->gend[gi] == '*')
		gi++;
	tempj = gi;
	tempi = ri;
	if (globs->gend[gi] == '\0') // no globend means every end matches
	{
		/*printf("ft_nextwildcard end of glob\n");*/
		return (1); // this one is a match
	}
	while (dname[ri]) // while there are characters in filename 
	{
		if (globs->gend[gi] == '\\' || dname[ri] == globs->gend[gi]) // if the first character matches or there is no globend
		{
			while (globs->gend[gi] == '\\' || (dname[ri] && globs->gend[gi] && dname[ri] == globs->gend[gi])) //while the first character was a match but globend exists
			{
				if (globs->gend[gi] == '\\')
				{
					/*printf("ft_nextwildcard found a \\ in gend\n");*/
					gi++;
				}
				else
				{
					/*printf("ft_nextwildcard fastmatch %c\n", dname[ri]);*/
					gi++;
					ri++;
				}
			}
			/*printf("ft_nextwildcard fastmatch break %c %c\n", dname[ri], globs->gend[gi]);*/
			if (globs->gend[gi - 1] != '\\' && globs->gend[gi] && ft_strchr("*?[", globs->gend[gi])) // if we find a new glob
			{
				/*printf("ft_nextwildcard glob found going into recursion\n");*/
				return (ft_nextglob(globs, dname, ri, gi)); // recursive glob function returns 1 if it eventually matches
			}
			if (dname[ri] == '\0') // the whole filename matches
			{
				/*printf("ft_nextwilcard reached end of dname\n");*/
				return (1); // copy it over.
			}
			else // we have no match and reset the globend counter.
			{
				/*printf("ft_nextwildcard skipping one character\n");*/
				gi = tempj;
			}
		}
		if (globs->gend[gi - 1] != '\\' && globs->gend[gi] && ft_strchr("*?[", globs->gend[gi])) // if we find a new glob
		{
			/*printf("ft_nextwildcard glob found going into recursion\n");*/
			return (ft_nextglob(globs, dname, ri, gi)); // recursive glob function returns 1 if it eventually matches
		}
		tempi++;
		ri = tempi;
	}
	return (0);
}

int	ft_firstwildcard(t_globs *globs, char *dname, int ri)
{
	int	temp;
	int	ret;
	int	gi;

	gi = 0;
	temp = ri;
	if (globs->gstart[0] != '.' && dname[0] == '.') // if there is a period mismatch
	{
		/*printf("ft_firstwildcard Periods don't match\n");*/
		return (0); // we don't want to parse this one.
	}
	while (globs->gend[gi] == '*')
		gi++;
	if (globs->gend[gi] == '\0' && dname[ri] == '\0')
		return (1);
	while (dname[ri]) // while there are characters in filename 
	{
		while (globs->gend[gi] == '*')
			gi++;
		/*printf("ft_firstwilcard trying to match dname %c with gend %c\n", dname[ri], globs->gend[gi]);*/
		if (dname[ri] == globs->gend[gi] || globs->gend[0] == '\0') // if the first character matches or there is no globend
		{
			if (globs->gend[0] == '\0') // no globend means every end matches
			{
				/*printf("ft_firstwildcard no characters after glob so this matches\n");*/
				return (1); // this one is a match
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
					/*printf("ft_firstwildcard fastmatch %c\n", dname[ri]);*/
					gi++;
					ri++;
				}
			}
			if (dname[ri] == '\0' && globs->gend[gi] == '\0') // the whole filename matches
			{
				/*printf("ft_firstwildcard whole filename matches\n");*/
				return (1); // copy it over.
			}
			if (ft_strchr("*?[", globs->gend[gi])) // if we find a new glob
			{
				if (globs->gend[gi - 1] == '\\')
				{
					/*printf("skipping this not glob\n");*/
				}
				else
				{
					/*printf("ft_firstwildcard recursive glob found\n");*/
					ret = ft_nextglob(globs, dname, ri, gi); // recursive glob function returns 1 if it eventually matches
					if (ret == 1)
						return (ret);
					ri++;
					gi = 0;
				}
			}
			else // we have no match and reset the globend counter.
			{
				ri++;
				gi = 0;
			}
		}
		else if (ft_strchr("*?[", globs->gend[gi])) // if we find a new glob
		{
			/*printf("ft_firstwildcard recursive glob found\n");*/
			ret = ft_nextglob(globs, dname, ri, gi); // recursive glob function returns 1 if it eventually matches
			if (ret == 1)
				return (ret);
			temp++;
			ri = temp;
		}
		else // no matching first character means we can move over a character and try to match from there.
		{
			temp++;
			ri = temp;
		}
	}
	/*printf("ft_firstwildcard return 0\n");*/
	return (0); // no matches found.
}
