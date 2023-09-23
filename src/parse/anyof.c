/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   anyof.c                                         |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: houtworm <codam@houtworm.net>              //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/09/20 00:51:38 by houtworm     /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/09/23 13:59:13 by houtworm     \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int		ft_nextsubanyof(t_globs *globs, int i, int j, int k)
{
	printf("ft_nextsubanyof starting with j: %d k: %d, dname: %c glob: %c\n", j, k, globs->tempsubdir[i][k], globs->subdir[i][j]);
	while (globs->tempsubdir[i][k] && globs->subdir[i][j] && globs->tempsubdir[i][k] == globs->subdir[i][j]) //while the characters match we skip them
	{
		printf("ft_nextsubanyof fastmatch: %c, %c\n", globs->subdir[i][j], globs->tempsubdir[i][k]);
		j++;
		k++;
	}
	printf("ft_nextsubanyof fastmatch broken: %c, %c\n", globs->subdir[i][j], globs->tempsubdir[i][k]);
	if (globs->subdir[i][j] == '\0' && globs->tempsubdir[i][k] == '\0') // if the end matches too
	{
		if (globs->temptype == DT_DIR) // check if it is a directory
		{
			printf("ft_nextsubanyof glob matches %s will be replaced with /%s in subdir %d\n", globs->subdir[i], globs->tempsubdir[i], i);
			return (1); // this one is a match
		}
		else
		{
			if (globs->subdir[i + 1])
			{
				printf("ft_nextsubanyof %s is not a dir and we need to go deeper so no match\n", globs->tempsubdir[i]);
				return (0);
			}
			else
			{
				printf("ft_nextsubanyof %s matches but is not a dir but we are at our dept so match\n", globs->tempsubdir[i]);
				return (1);
			}
		}
	}
	if (globs->tempsubdir[i][j] == '\0' || globs->tempsubdir[i][k] == '\0') // mismatch
	{
		return (0);
	}
	if (globs->subdir[i][j + 1] == '\0' && globs->tempsubdir[i][j + 1] == '\0') // if there is a mismatch
	{
		return (1);
	}
	else if (globs->subdir[i][j] && ft_strchr("*?[", globs->subdir[i][j])) // if we find a new glob
	{
		printf("ft_nextsubanyof found glob going into recursion\n");
		return (ft_nextsubglob(globs, i, j + 1, j + 1)); // recursive glob function returns 1 if it eventually matches
	}
	return (0);
}

int		ft_firstsubanyof(t_globs *globs, struct dirent *dirents, int i, int itar)
{
	while (dirents->d_name[itar] && globs->subdir[i][itar] && dirents->d_name[itar] == globs->subdir[i][itar]) //while the characters match we skip them
	{
		printf("ft_firstsubanyof fastmatch: %c, %c\n", globs->subdir[i][itar], dirents->d_name[itar]);
		itar++;
	}
	printf("ft_firstsubanyof fastmatch broken: %c, %c\n", globs->subdir[i][itar], dirents->d_name[itar]);
	if (globs->subdir[i][itar] == '\0' && dirents->d_name[itar] == '\0') // if the end matches too
	{
		if (dirents->d_type == DT_DIR) // check if it is a directory
		{
			printf("ft_firstsubanyof glob matches %s will be replaced with /%s in subdir %d\n", globs->subdir[i], dirents->d_name, i);
			globs->tempsubdir[i] = ft_strjoin("/", dirents->d_name);
			return (1); // this one is a match
		}
		else
		{
			if (globs->subdir[i + 1])
			{
				printf("ft_firstsubanyof %s is not a dir and we need to go deeper so no match\n", dirents->d_name);
				return (0);
			}
			else
			{
				globs->tempsubdir[i] = ft_strjoin("/", dirents->d_name);
				printf("ft_firstsubanyof %s matches but is not a dir but we are at our dept so match\n", dirents->d_name);
				return (1);
			}
		}
	}
	if (globs->subdir[i][itar] == '\0' || dirents->d_name[itar] == '\0') // if there is a mismatch
	{
		return (0);
	}
	if (globs->subdir[i][itar + 1] == '\0' && dirents->d_name[itar + 1] == '\0') // if there is a mismatch
	{
		return (1);
	}
	if (globs->subdir[i][itar] && ft_strchr("*?[", globs->subdir[i][itar])) // if we find a new glob
	{
		printf("ft_firstsubanyof found glob going into recursion\n");
		globs->tempsubdir[i] = ft_strjoin("/", dirents->d_name);
		globs->temptype = dirents->d_type;
		if (ft_nextsubglob(globs, i, itar, itar)) // recursive glob function returns 1 if it eventually matches
		{
			if (dirents->d_type == DT_DIR) // check if it is a directory
			{
				printf("ft_firstsubanyof glob matches %s will be replaced with /%s in subdir %d\n", globs->subdir[i], dirents->d_name, i);
				globs->tempsubdir[i] = ft_strjoin("/", dirents->d_name);
				return (1); // this one is a match
			}
			else
			{
				if (globs->subdir[i + 1])
				{
					printf("ft_firstsubanyof %s is not a dir and we need to go deeper so no match\n", dirents->d_name);
					return (0);
				}
				else
				{
					globs->tempsubdir[i] = ft_strjoin("/", dirents->d_name);
					printf("ft_firstsubanyof %s matches but is not a dir but we are at our dept so match\n", dirents->d_name);
					return (1);
				}
			}
		}
		else
			return (0);
	}
	printf("ft_firstsubanyof return 0?\n");
	return (0);
}

int	ft_nextanyof(t_globs *globs, char *dname, int i, int j)
{
	char	match;
	int		k;

	k = 0;
	match = dname[i];
	while (globs->gend[j] && globs->gend[j] != ']')
	{
		globs->anyof[k] = globs->gend[j];
		j++;
		k++;
	}
	if (!globs->gend[j])
		return (0);
	globs->anyof[k] = '\0';
	printf("gend: %s\n", globs->gend);
	printf("anyof: %s\n", globs->anyof);
	printf("dname: %s\n", dname);
	printf("i: %d, j: %d\n", i, j);
	/*j++;*/
	/*j++;*/
	printf("ft_nextanyof starting with dname: %c and anyof: %s\n", dname[i], globs->anyof);
	if (ft_strchr(globs->anyof, match)) // if any of the characters in the anyof match
	{
		printf("ft_nextanyof anyof matches %c\n", match);
		j = j + ft_strlen(globs->anyof);
		i++;
	}
	while (dname[i] && globs->gend[j] && dname[i] == globs->gend[j])
	{
		printf("ft_firstanyof fastmatch %c\n", dname[i]);
		j++;
		i++;
	}
	printf("ft_nextanyof fastmatch break %c %c %d, %d\n", dname[i], globs->gend[j], i, j);
	if (dname[i] && globs->gend[j] && ft_strchr("*?[", globs->gend[j])) // if we find a new glob
	{
		printf("ft_nextanyof glob found going into recursion\n");
		return (ft_nextglob(globs, dname, i, j)); // recursive glob function returns 1 if it eventually matches
	}
	if (globs->gend[j] == '\0' && dname[i] == '\0') // the whole filename matches
	{
		printf("ft_nextwilcard reached end of dname\n");
		return (1); // copy it over.
	}
	return (0);
}

int	ft_firstanyof(t_globs *globs, char *dname, int i)
{
	int	j;

	j = 0;
	while (globs->gend[j] && globs->gend[j] != ']')
	{
		globs->glob[j + 1] = globs->gend[j];
		globs->anyof[j] = globs->gend[j];
		j++;
	}
	if (!globs->gend[j])
		return (0);
	globs->anyof[j] = '\0';
	globs->glob[j + 1] = ']';
	globs->gend = ft_substr(globs->gend, j + 1, ft_strlen(globs->gend));
	printf("gend: %s\n", globs->gend);
	printf("glob: %s\n", globs->glob);
	printf("gstart: %s\n", globs->gstart);
	printf("anyof: %s\n", globs->anyof);
	printf("dname: %s\n", dname);
	j = 0;
	printf("ft_firstanyof starting with dname: %c and anyof: %s\n", dname[i + j], globs->anyof);
	if (ft_strchr(globs->anyof, dname[i])) // if any of the characters in the anyof match
	{
		printf("ft_firstanyof matches %c\n", dname[i + j]);
		j = j + ft_strlen(globs->anyof);
		i++;
		/*j++;*/
		while (dname[i] && globs->gend[j - 1] && dname[i] == globs->gend[j - 1])
		{
			printf("ft_firstanyof fastmatch %c\n", dname[i]);
			j++;
			i++;
		}
		printf("ft_firstanyof fastmatch break %c\n", dname[i]);
		if (dname[i] == '\0' && globs->gend[j - 1] == '\0') // the whole filename matches
		{
			printf("ft_firstanyof whole filename matches\n");
			return (1); // copy it over.
		}
		if (dname[i] == '\0' || globs->gend[j - 1] == '\0') // mismatch
		{
			printf("ft_firstanyof mistmatch i: %d, j: %d, nam: %c, end: %c\n", i, j, dname[i], globs->gend[j - 1]);
			return (0);
		}
		if (ft_strchr("*?[", globs->gend[j - 1])) // if we find a new glob
		{
			printf("ft_firstanyof recursive glob found\n");
			return (ft_nextglob(globs, dname, i, j - 1)); // recursive glob function returns 1 if it eventually matches
		}
	}
	printf("ft_firstanyof return 0\n");
	return (0); // no matches found.
}
