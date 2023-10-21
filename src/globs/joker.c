/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   joker.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: houtworm <codam@houtworm.net>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/20 00:51:17 by houtworm      #+#    #+#                 */
/*   Updated: 2023/10/21 09:04:26 by houtworm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_nextjoker(t_globs *globs, char *dname, int ri, int gi)
{
	while (globs->gend[gi] == '\\' || \
			(dname[ri] && globs->gend[gi] && dname[ri] == globs->gend[gi]))
	{
		if (globs->gend[gi] == '\\')
			gi++;
		else
		{
			gi++;
			ri++;
		}
	}
	if (dname[ri] && globs->gend[gi] && \
			ft_strchr("*?[", globs->gend[gi]) && globs->gend[gi - 1] != '\\')
		return (ft_nextglob(globs, dname, ri, gi));
	if (globs->gend[gi] == '\0' && dname[ri] == '\0')
		return (1);
	if (globs->gend[gi - 1] != '\\' && \
			globs->gend[gi] == '*' && dname[ri] == '\0')
		return (ft_nextglob(globs, dname, ri, gi));
	if (globs->gend[gi] == '\0' || dname[ri] == '\0')
		return (0);
	return (0);
}

int	ft_firstjoker(t_globs *globs, char *dname, int ri)
{
	int	gi;

	gi = 0;
	if (globs->gsta[0] != '.' && dname[0] == '.')
		return (0);
	while (globs->gend[gi] == '\\' || \
			(dname[ri] && globs->gend[gi] && dname[ri] == globs->gend[gi]))
	{
		if (globs->gend[gi] == '\\')
			gi++;
		else
		{
			gi++;
			ri++;
		}
	}
	if (dname[ri] == '\0' && globs->gend[gi] == '\0')
		return (1);
	if (dname[ri] == '\0' || globs->gend[gi] == '\0')
		return (0);
	if (ft_strchr("*?[", globs->gend[gi]))
		return (ft_nextglob(globs, dname, ri, gi));
	return (0);
}
