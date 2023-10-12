/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   anyof.c                                         |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: houtworm <codam@houtworm.net>              //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/09/20 00:51:38 by houtworm     /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/10/12 21:04:37 by houtworm     \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int		ft_nextsubanyof(t_globs *globs, int si, int ri, int gi)
{
	int		l;

	l = 0;
	while (globs->subdir[si][gi] && globs->subdir[si][gi] != ']')
	{
		globs->anyof[l] = globs->subdir[si][gi];
		gi++;
		l++;
	}
	if (!globs->subdir[si][gi])
		return (0);
	globs->anyof[l] = '\0';
	if (globs->anyof[0] == '\0')
		return (0);
	/*printf("ft_nextsubanyof starting with ri: %d gi: %d, dname: %c glob: %c\n", ri, gi, globs->tempsubdir[si][ri], globs->subdir[si][gi]);*/
	if (ft_strchr(globs->anyof, globs->tempsubdir[si][ri])) // if any of the characters in the anyof match
	{
		/*printf("ft_nextsubanyof anyof matches: %c, %c\n", globs->subdir[si][gi], globs->tempsubdir[si][ri]);*/
		gi++;
		ri++;
	}
	while (globs->subdir[si][gi] == '\\' || (globs->subdir[si][gi] && globs->tempsubdir[si][ri] && globs->tempsubdir[si][ri] == globs->subdir[si][gi]))
	{
		if (globs->subdir[si][gi] == '\\')
			gi++;
		else
		{
			/*printf("ft_nextsubanyof fastmatch %c\n", globs->tempsubdir[si][ri]);*/
			ri++;
			gi++;
		}
	}
	/*printf("ft_nextsubanyof fastmatch broken: %c, %c\n", globs->subdir[si][gi], globs->tempsubdir[si][ri]);*/
	if (globs->subdir[si][gi] == '\0' && globs->tempsubdir[si][ri] == '\0') // if the end matches too
	{
		if (globs->temptype == DT_DIR) // check if it is a directory
		{
			/*printf("ft_nextsubanyof glob matches %s will be replaced with /%s in subdir %d\n", globs->subdir[si], globs->tempsubdir[si], si);*/
			return (1); // this one is a match
		}
		else
		{
			if (globs->subdir[si + 1])
			{
				/*printf("ft_nextsubanyof %s is not a dir and we need to go deeper so no match\n", globs->tempsubdir[si]);*/
				return (0);
			}
			else
			{
				/*printf("ft_nextsubanyof %s matches but is not a dir but we are at our dept so match\n", globs->tempsubdir[si]);*/
				return (1);
			}
		}
	}
	/*if (globs->subdir[si][gi] == '\0' || globs->tempsubdir[si][ri] == '\0') // mismatch*/
	/*{*/
		/*return (0);*/
	/*}*/
	/*if (globs->subdir[si][gi] == '\0' && globs->tempsubdir[si][ri] == '\0') // we are at the end*/
	/*{*/
		/*return (1);*/
	/*}*/
	else if (globs->subdir[si][gi - 1] != '\\' && globs->subdir[si][gi] && ft_strchr("*?[", globs->subdir[si][gi])) // if we find a new glob
	{
		/*printf("ft_nextsubanyof found glob going into recursion\n");*/
		return (ft_nextsubglob(globs, si, ri, gi)); // recursive glob function returns 1 if it eventually matches
	}
	return (0);
}

int		ft_firstsubanyof(t_globs *globs, struct dirent *dirents, int si, int gi)
{
	int	ri;

	ri = 0;
	while (globs->subdir[si][gi] && (globs->subdir[si][gi] != ']' || globs->subdir[si][gi - 1] == '\\'))
	{
		globs->anyof[ri] = globs->subdir[si][gi];
		ri++;
		gi++;
	}
	if (!globs->subdir[si][gi])
		return (0);
	globs->anyof[ri] = '\0';
	if (globs->anyof[0] == '\0')
		return (0);
	ri = 0;
	gi++;
	while (globs->subdir[si][ri + 1] != '[' || globs->subdir[si][ri] == '\\')
		ri++;
	/*printf("ft_firstsubanyof starting with dname: %c and anyof: %s\n", dirents->d_name[ri], globs->anyof);*/
	if (ft_strchr(globs->anyof, dirents->d_name[ri])) // if any of the characters in the anyof match
	{
		/*printf("ft_firstsubanyof anyof matches %c\n", dirents->d_name[ri]);*/
		ri++;
		while (globs->subdir[si][gi] == '\\' || (globs->subdir[si][gi] && dirents->d_name[ri] && dirents->d_name[ri] == globs->subdir[si][gi]))
		{
			if (globs->subdir[si][gi] == '\\')
				gi++;
			else
			{
				/*printf("ft_firstsubanyof fastmatch %c\n", dirents->d_name[ri]);*/
				gi++;
				ri++;
			}
		}
		/*printf("ft_firstsubanyof fastmatch break %c %c\n", dirents->d_name[ri], globs->subdir[si][gi]);*/
		if (dirents->d_name[ri] == '\0' && globs->subdir[si][gi] == '\0') // the whole filename matches
		{
			/*printf("ft_firstsubanyof whole filename matches\n");*/
			if (dirents->d_type == DT_DIR) // check if it is a directory
			{
				/*printf("ft_firstsubanyof glob matches %s will be replaced with /%s in subdir %d\n", globs->subdir[si], dirents->d_name, si);*/
				free(globs->tempsubdir[si]);
				globs->tempsubdir[si] = ft_strjoin("/", dirents->d_name);
				return (1); // this one is a match
			}
			else
			{
				if (globs->subdir[si + 1])
				{
					/*printf("ft_firstsubanyof %s is not a dir and we need to go deeper so no match\n", dirents->d_name);*/
					return (0);
				}
				else
				{
					free(globs->tempsubdir[si]);
					globs->tempsubdir[si] = ft_strjoin("/", dirents->d_name);
					/*printf("ft_firstsubanyof %s matches but is not a dir but we are at our dept so match\n", dirents->d_name);*/
					return (1);
				}
			}
		}
		if (dirents->d_name[ri] == '\0' || globs->subdir[si][gi] == '\0') // mismatch
		{
			/*printf("ft_firstsubanyof mistmatch ri: %d, gi: %d, nam: %c, end: %c\n", gi, ri, dirents->d_name[ri], globs->subdir[si][gi]);*/
			return (0);
		}
		if (globs->subdir[si][gi] && ft_strchr("*?[", globs->subdir[si][gi])) // if we find a new glob
		{
			/*printf("ft_firstsubanyof recursive glob found\n");*/
			globs->temptype = dirents->d_type;
			free(globs->tempsubdir[si]);
			globs->tempsubdir[si] = ft_strjoin("/", dirents->d_name);
			return (ft_nextsubglob(globs, si, ri + 1, gi)); // recursive glob function returns 1 if it eventually matches
		}
	}
	/*printf("ft_firstsubanyof return 0?\n");*/
	return (0);
}

int	ft_nextanyof(t_globs *globs, char *dname, int ri, int gi)
{
	char	match;
	int		k;

	k = 0;
	match = dname[ri];
	while (globs->gend[gi] && globs->gend[gi] != ']')
	{
		globs->anyof[k] = globs->gend[gi];
		gi++;
		k++;
	}
	if (!globs->gend[gi])
		return (0);
	globs->anyof[k] = '\0';
	if (globs->anyof[0] == '\0')
		return (0);
	/*printf("ft_nextanyof starting with dname: %c and anyof: %s\n", dname[ri], globs->anyof);*/
	if (ft_strchr(globs->anyof, match)) // if any of the characters in the anyof match
	{
			/*printf("ft_nextanyof anyof matches %c\n", match);*/
			gi++;
			ri++;
	}
	while (globs->gend[gi] == '\\' || (dname[ri] && globs->gend[gi] && dname[ri] == globs->gend[gi]))
	{
		if (globs->gend[gi] == '\\')
		{
			/*printf("ft_nextanyof found a \\ in gend\n");*/
			gi++;
		}
		else
		{
			/*printf("ft_nextanyof fastmatch %c\n", dname[ri]);*/
			gi++;
			ri++;
		}
	}
	/*printf("ft_nextanyof fastmatch break %c %c %d, %d\n", dname[ri], globs->gend[gi], ri, gi);*/
	if (globs->gend[gi - 1] != '\\' && globs->gend[gi] && ft_strchr("*?[", globs->gend[gi])) // if we find a new glob
	{
		/*printf("ft_nextanyof glob found going into recursion\n");*/
		return (ft_nextglob(globs, dname, ri, gi)); // recursive glob function returns 1 if it eventually matches
	}
	if (globs->gend[gi] == '\0' && dname[ri] == '\0') // the whole filename matches
	{
		/*printf("ft_nextanyof reached end of dname\n");*/
		return (1); // copy it over.
	}
	return (0);
}

int	ft_firstanyof(t_globs *globs, char *dname, int ri)
{
	int		gi;
	char	*temp;

	gi = 0;
	/*printf("ft_firstanyof baby\n");*/
	if (!globs->anyof[0])
	{
		while (globs->gend[gi] && globs->gend[gi] != ']')
		{
			globs->glob[gi + 1] = globs->gend[gi];
			globs->anyof[gi] = globs->gend[gi];
			gi++;
		}
		if (!globs->gend[gi])
		{
			/*printf("no globs->gend[gi]\n");*/
			return (0);
		}
		globs->anyof[gi] = '\0';
		globs->glob[gi + 1] = ']';
		temp = ft_substr(globs->gend, gi + 1, ft_strlen(globs->gend));
		free(globs->gend);
		globs->gend = ft_strdup(temp);
		free(temp);
	}
	else
	{
		while (globs->glob[gi + 1] && globs->glob[gi + 1] != ']')
		{
			globs->anyof[gi] = globs->glob[gi + 1];
			gi++;
		}
		if (!globs->glob[gi + 1])
		{
			/*printf("no globs->glob[gi + 1]\n");*/
			return (0);
		}
		globs->anyof[gi] = '\0';
	}
	if (globs->anyof[0] == '\0')
		return (0);
	/*printf("ft_firstanyof starting with dname: %c and anyof: %s\n", dname[ri], globs->anyof);*/
	if (ft_strchr(globs->anyof, dname[ri])) // if any of the characters in the anyof match
	{
		/*printf("ft_firstanyof anyof matches %c\n", dname[ri]);*/
		gi = 0;
		ri++;
		while (globs->gend[gi] == '\\' || (dname[ri] && globs->gend[gi] && dname[ri] == globs->gend[gi]))
		{
			if (globs->gend[gi] == '\\')
			{
				/*printf("ft_firstwildcard found a \\\n");*/
				gi++;
			}
			else
			{
				/*printf("ft_firstanyof fastmatch %c\n", dname[ri]);*/
				gi++;
				ri++;
			}
		}
		/*printf("ft_firstanyof fastmatch break %c %c\n", dname[ri], globs->gend[gi]);*/
		if (dname[ri] == '\0' && globs->gend[gi] == '\0') // the whole filename matches
		{
			/*printf("ft_firstanyof whole filename matches\n");*/
			return (1); // copy it over.
		}
		if (dname[ri] == '\0' || globs->gend[gi] == '\0') // mismatch
		{
			/*printf("ft_firstanyof mismatch ri: %d, gi: %d, nam: %c, end: %c\n", ri, gi, dname[ri], globs->gend[gi]);*/
			return (0);
		}
		if (ft_strchr("*?[", globs->gend[gi])) // if we find a new glob
		{
			/*printf("ft_firstanyof recursive glob found\n");*/
			return (ft_nextglob(globs, dname, ri, gi)); // recursive glob function returns 1 if it eventually matches
		}
	}
	/*printf("ft_firstanyof return 0\n");*/
	return (0); // no matches found.
}
