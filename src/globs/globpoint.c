/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   globpoint.c                                     |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: houtworm <codam@houtworm.net>              //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/09/20 03:29:43 by houtworm     /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/10/12 17:03:12 by houtworm     \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int		ft_nextsubglob(t_globs *globs, int i, int j, int k)
{
	if (globs->subdir[i][j] == '*')
	{
		/*printf("ft_nextsubglob found * glob going into nextsubwildcard i: %d j: %d k: %d\n", i, j, k);*/
		return (ft_nextsubwildcard(globs, i, j, k));
	}
	if (globs->subdir[i][j] == '?')
	{
		/*printf("ft_nextsubglob found ? glob going into nextsubjoker i: %d j: %d k: %d\n", i, j + 1, k + 1);*/
		return (ft_nextsubjoker(globs, i, j + 1, k + 1));
	}
	if (globs->subdir[i][j] == '[')
	{
		/*printf("ft_nextsubglob found [ glob going into nextsubanyof i: %d j: %d k: %d\n", i, j + 1, k);*/
		return (ft_nextsubanyof(globs, i, j + 1, k));
	}
	return (0);
}

int		ft_firstsubglob(t_globs *globs, struct dirent *dirents, int i, int j)
{
	if (globs->subdir[i][j] == '*')
	{
		/*printf("ft_firstsubglob found * glob going into firstsubwildcard i: %d j: %d\n", i, j);*/
		return (ft_firstsubwildcard(globs, dirents, i, j));
	}
	if (globs->subdir[i][j] == '?')
	{
		/*printf("ft_firstsubglob found ? glob going into firstsubjoker i: %d j: %d\n", i, j);*/
		return (ft_firstsubjoker(globs, dirents, i, j));
	}
	if (globs->subdir[i][j] == '[')
	{
		/*printf("ft_firstsubglob found [ glob going into firstsubanyof i: %d j: %d\n", i, j + 1);*/
		return (ft_firstsubanyof(globs, dirents, i, j + 1));
	}
	return (0);
}

int	ft_nextglob(t_globs *globs, char *dname, int i, int j)
{
	if (globs->gend[j] == '*')
	{
		/*printf("ft_nextglob found * glob going into nextwildcard i: %d j: %d\n", i, j);*/
		return (ft_nextwildcard(globs, dname, i, j));
	}
	if (globs->gend[j] == '?')
	{
		/*printf("ft_nextglob found ? glob going into nextjoker i: %d j: %d\n", i + 1, j + 1);*/
		return (ft_nextjoker(globs, dname, i + 1, j + 1));
	}
	if (globs->gend[j] == '[')
	{
		/*printf("ft_nextglob found [ glob going into nextanyof i: %d j: %d\n", i, j);*/
		return (ft_nextanyof(globs, dname, i, j + 1));
	}
	return (0);
}

int	ft_firstglob(t_globs *globs, char *dname, int i)
{ // maybe put a while loop here to handle multiple globs in the same path dir
	if (globs->glob[0] == '*') // if we find a wildcard match
		return (ft_firstwildcard(globs, dname, i)); // parse it
	if (globs->glob[0] == '?') // if we find a joker match
		return (ft_firstjoker(globs, dname, i + 1)); // parse it
	if (globs->glob[0] == '[') // if we find a anyof match
		return (ft_firstanyof(globs, dname, i)); // parse it
	return (0);
}
