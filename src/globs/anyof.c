/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   anyof.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: houtworm <codam@houtworm.net>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/20 00:51:38 by houtworm      #+#    #+#                 */
/*   Updated: 2023/10/23 13:02:35 by houtworm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_matchanyof(char *glob, int ri, int gi, char match)
{
	int	k;
	char *anyof;

	k = 0;
	anyof = ft_calloc(ft_strlen(glob), 8);
	while (glob[gi] && glob[gi] != ']')
	{
		anyof[k] = glob[gi];
		gi++;
		k++;
	}
	if (!glob[gi] || k == 0)
	{
		free(anyof);
		return (0);
	}
	if (ft_strchr(anyof, match))
	{
		gi++;
		ri++;
		free(anyof);
		return (gi);
	}
	free(anyof);
	return (0);
}

int	ft_nextanyof(t_globs *globs, char *dname, int ri, int gi)
{
	gi = ft_matchanyof(globs->gend, ri, gi, dname[ri]);
	if (gi == 0)
		return (0);
	else
		ri++;
	while (globs->gend[gi] == '\\' || (dname[ri] && globs->gend[gi] && dname[ri] == globs->gend[gi]))
	{
		if (globs->gend[gi] != '\\')
			ri++;
		gi++;
	}
	if (globs->gend[gi - 1] != '\\' && globs->gend[gi] && ft_strchr("*?[", globs->gend[gi]))
		return (ft_nextglob(globs, dname, ri, gi));
	if (globs->gend[gi] == '\0' && dname[ri] == '\0')
		return (1);
	return (0);
}

int	ft_firstanyof(t_globs *globs, char *dname, int ri)
{
	int		gi;

	gi = 0;
	gi = ft_matchanyof(globs->gend, ri, gi, dname[ri]);
	if (gi == 0)
		return (0);
	else
		ri++;
	while (globs->gend[gi] == '\\' || (dname[ri] && globs->gend[gi] && dname[ri] == globs->gend[gi]))
	{
		if (globs->gend[gi] != '\\')
			ri++;
		gi++;
	}
	if (dname[ri] == '\0' && globs->gend[gi] == '\0')
		return (1);
	if (dname[ri] == '\0' || globs->gend[gi] == '\0')
		return (0);
	if (ft_strchr("*?[", globs->gend[gi]))
		return (ft_nextglob(globs, dname, ri, gi));
	return (0);
}
