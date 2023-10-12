/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   globpoint.c                                     |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: houtworm <codam@houtworm.net>              //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/09/20 03:29:43 by houtworm     /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/10/12 21:00:39 by houtworm     \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int		ft_nextsubglob(t_globs *globs, int si, int ri, int gi)
{
	if (globs->subdir[si][gi] == '*')
	{
		/*printf("ft_nextsubglob found * glob going into nextsubwildcard si: %d ri: %d gi: %d\n", si, ri, gi);*/
		return (ft_nextsubwildcard(globs, si, ri, gi));
	}
	if (globs->subdir[si][gi] == '?')
	{
		/*printf("ft_nextsubglob found ? glob going into nextsubjoker si: %d ri: %d gi: %d\n", si, ri + 1, gi + 1);*/
		return (ft_nextsubjoker(globs, si, ri + 1, gi + 1));
	}
	if (globs->subdir[si][gi] == '[')
	{
		/*printf("ft_nextsubglob found [ glob going into nextsubanyof si: %d ri: %d gi: %d\n", si, ri + 1, gi);*/
		return (ft_nextsubanyof(globs, si, ri, gi + 1));
	}
	return (0);
}

int		ft_firstsubglob(t_globs *globs, struct dirent *dirents, int si, int gi)
{
	if (globs->subdir[si][gi] == '*')
	{
		/*printf("ft_firstsubglob found * glob going into firstsubwildcard si: %d gi: %d\n", si, gi);*/
		return (ft_firstsubwildcard(globs, dirents, si, gi));
	}
	if (globs->subdir[si][gi] == '?')
	{
		/*printf("ft_firstsubglob found ? glob going into firstsubjoker si: %d gi: %d\n", si, gi);*/
		return (ft_firstsubjoker(globs, dirents, si, gi));
	}
	if (globs->subdir[si][gi] == '[')
	{
		/*printf("ft_firstsubglob found [ glob going into firstsubanyof si: %d gi: %d\n", si, gi + 1);*/
		return (ft_firstsubanyof(globs, dirents, si, gi + 1));
	}
	return (0);
}

int	ft_nextglob(t_globs *globs, char *dname, int ri, int gi)
{
	if (globs->gend[gi] == '*')
	{
		/*printf("ft_nextglob found * glob going into nextwildcard ri: %d gi: %d\n", ri, gi);*/
		return (ft_nextwildcard(globs, dname, ri, gi));
	}
	if (globs->gend[gi] == '?')
	{
		/*printf("ft_nextglob found ? glob going into nextjoker ri: %d gi: %d\n", ri + 1, gi + 1);*/
		return (ft_nextjoker(globs, dname, ri + 1, gi + 1));
	}
	if (globs->gend[gi] == '[')
	{
		/*printf("ft_nextglob found [ glob going into nextanyof ri: %d gi: %d\n", ri, gi);*/
		return (ft_nextanyof(globs, dname, ri, gi + 1));
	}
	return (0);
}

int	ft_firstglob(t_globs *globs, char *dname, int ri)
{ // maybe put a while loop here to handle multiple globs in the same path dir
	if (globs->glob[0] == '*') // if we find a wildcard match
		return (ft_firstwildcard(globs, dname, ri)); // parse it
	if (globs->glob[0] == '?') // if we find a joker match
		return (ft_firstjoker(globs, dname, ri + 1)); // parse it
	if (globs->glob[0] == '[') // if we find a anyof match
		return (ft_firstanyof(globs, dname, ri)); // parse it
	return (0);
}
