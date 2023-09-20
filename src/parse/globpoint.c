/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   globpoint.c                                     |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: houtworm <codam@houtworm.net>              //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/09/20 03:29:43 by houtworm     /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/09/20 03:57:23 by houtworm     \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int		ft_recursivesubdir(t_globs *globs, struct dirent *dirents, int i, int j)
{
	if (globs->subdir[i][j] == '*')
	{
		printf("ft_recursivesubdir found * glob going into recursivesubwildcard i: %d j: %d\n", i, j);
		return (ft_recursivesubwildcard(globs, dirents, i, j + 1));
	}
	if (globs->subdir[i][j] == '?')
	{
		printf("ft_recursivesubdir found ? glob going into recursivesubjoker i: %d j: %d\n", i, j);
		return (ft_recursivesubjoker(globs, dirents, i, j + 1));
	}
	if (globs->subdir[i][j] == '[')
	{
		printf("ft_recursivesubdir found [ glob going into recursivesubanyof i: %d j: %d\n", i, j);
		return (ft_recursivesubanyof(globs, dirents, i, j + 1));
	}
	return (0);
}


int	ft_recursiveglob(t_globs *globs, char *dname, int i, int j)
{
	if (globs->gend[j] == '*')
	{
		return (ft_recursivewildcard(globs, dname, i, j + 1));
	}
	if (globs->gend[j] == '?')
	{
		ft_recursivejoker(globs, dname, i, j + 1);
	}
	if (globs->gend[j] == '[')
	{
		ft_recursiveanyof(globs, dname, i, j + 1);
	}
	return (0);
}

int	ft_matchglob(t_globs *globs, char *dname, int i)
{ // maybe put a while loop here to handle multiple globs in the same path dir
	if (globs->glob[0] == '*') // if we find a wildcard match
		if (ft_parsewildcard(globs, dname, i)) // parse it
			return (1);
	if (globs->glob[0] == '?')
		if (ft_parsejoker(globs, dname, i))
			return (1);
	if (globs->glob[0] == '[')
		if (ft_parseanyof(globs, dname, i))
			return (1);
	return (0);
}
