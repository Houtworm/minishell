/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   globpoint.c                                     |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: houtworm <codam@houtworm.net>              //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/09/20 03:29:43 by houtworm     /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/09/21 06:14:13 by djonker      \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int		ft_nextsubglob(t_globs *globs, int i, int j, int k)
{
	if (globs->subdir[i][j] == '*')
	{
		printf("ft_nextsubglob found * glob going into nextsubwildcard i: %d j: %d k: %d\n", i, j, k);
		return (ft_nextsubwildcard(globs, i, j + 1, k));
	}
	/*if (globs->subdir[i][j] == '?')*/
	/*{*/
		/*printf("ft_recursivesubdir found ? glob going into recursivesubjoker i: %d j: %d\n", i, j);*/
		/*return (ft_recursivesubjoker(globs, dirents, i, j + 1));*/
	/*}*/
	/*if (globs->subdir[i][j] == '[')*/
	/*{*/
		/*printf("ft_recursivesubdir found [ glob going into recursivesubanyof i: %d j: %d\n", i, j);*/
		/*return (ft_recursivesubanyof(globs, dirents, i, j + 1));*/
	/*}*/
	return (0);
}

int		ft_firstsubglob(t_globs *globs, struct dirent *dirents, int i, int j)
{
	if (globs->subdir[i][j] == '*')
	{
		printf("ft_firstsubglob found * glob going into firstsubwildcard i: %d j: %d\n", i, j);
		return (ft_firstsubwildcard(globs, dirents, i, j + 1));
	}
	/*if (globs->subdir[i][j] == '?')*/
	/*{*/
		/*printf("ft_recursivesubdir found ? glob going into recursivesubjoker i: %d j: %d\n", i, j);*/
		/*return (ft_recursivesubjoker(globs, dirents, i, j + 1));*/
	/*}*/
	/*if (globs->subdir[i][j] == '[')*/
	/*{*/
		/*printf("ft_recursivesubdir found [ glob going into recursivesubanyof i: %d j: %d\n", i, j);*/
		/*return (ft_recursivesubanyof(globs, dirents, i, j + 1));*/
	/*}*/
	return (0);
}

int	ft_nextglob(t_globs *globs, char *dname, int i, int j)
{
	if (globs->gend[j] == '*')
	{
		printf("ft_nextglob found * glob going into nextwildcard i: %d j: %d\n", i, j);
		return (ft_nextwildcard(globs, dname, i, j + 1));
	}
	/*if (globs->gend[j] == '?')*/
	/*{*/
		/*ft_recursivejoker(globs, dname, i, j + 1);*/
	/*}*/
	/*if (globs->gend[j] == '[')*/
	/*{*/
		/*ft_recursiveanyof(globs, dname, i, j + 1);*/
	/*}*/
	return (0);
}

int	ft_firstglob(t_globs *globs, char *dname, int i)
{ // maybe put a while loop here to handle multiple globs in the same path dir
	if (globs->glob[0] == '*') // if we find a wildcard match
		if (ft_firstwildcard(globs, dname, i)) // parse it
			return (1);
	/*if (globs->glob[0] == '?')*/
		/*if (ft_firstjoker(globs, dname, i))*/
			/*return (1);*/
	/*if (globs->glob[0] == '[')*/
		/*if (ft_firstanyof(globs, dname, i))*/
			/*return (1);*/
	return (0);
}
