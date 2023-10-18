/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   globpoint.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: houtworm <codam@houtworm.net>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/20 03:29:43 by houtworm      #+#    #+#                 */
/*   Updated: 2023/10/18 17:01:00 by houtworm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int		ft_nextsubglob(t_globs *globs, int si, int ri, int gi)
{
	if (globs->subdir[si][gi] == '*')
		return (ft_nextsubwildcard(globs, si, ri, gi));
	if (globs->subdir[si][gi] == '?')
		return (ft_nextsubjoker(globs, si, ri + 1, gi + 1));
	if (globs->subdir[si][gi] == '[')
		return (ft_nextsubanyof(globs, si, ri, gi + 1));
	return (0);
}

int		ft_firstsubglob(t_globs *globs, struct dirent *dirents, int si, int gi)
{
	if (globs->subdir[si][gi] == '*')
		return (ft_firstsubwildcard(globs, dirents, si, gi));
	if (globs->subdir[si][gi] == '?')
		return (ft_firstsubjoker(globs, dirents, si, gi));
	if (globs->subdir[si][gi] == '[')
		return (ft_firstsubanyof(globs, dirents, si, gi + 1));
	return (0);
}

int	ft_nextglob(t_globs *globs, char *dname, int ri, int gi)
{
	if (globs->gend[gi] == '*')
		return (ft_nextwildcard(globs, dname, ri, gi));
	if (globs->gend[gi] == '?')
		return (ft_nextjoker(globs, dname, ri + 1, gi + 1));
	if (globs->gend[gi] == '[')
		return (ft_nextanyof(globs, dname, ri, gi + 1));
	return (0);
}

int	ft_firstglob(t_globs *globs, char *dname, int ri)
{
	if (globs->glob[0] == '*')
		return (ft_firstwildcard(globs, dname, ri));
	if (globs->glob[0] == '?')
		return (ft_firstjoker(globs, dname, ri + 1));
	if (globs->glob[0] == '[')
		return (ft_firstanyof(globs, dname, ri));
	return (0);
}
