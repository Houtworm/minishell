/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   wildcard.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: houtworm <codam@houtworm.net>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/27 08:14:23 by houtworm      #+#    #+#                 */
/*   Updated: 2023/10/21 13:14:21 by djonker       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_nextwildcard(t_globs *globs, char *dname, int ri, int gi)
{
	int		tempj;
	int		tempi;

	while (globs->gend[gi] == '*')
		gi++;
	tempj = gi;
	tempi = ri;
	if (globs->gend[gi] == '\0')
		return (1);
	while (dname[ri])
	{
		if (globs->gend[gi] == '\\' || dname[ri] == globs->gend[gi])
		{
			while (globs->gend[gi] == '\\' || (dname[ri] && globs->gend[gi] && dname[ri] == globs->gend[gi]))
			{
				if (globs->gend[gi] != '\\')
					ri++;
				gi++;
			}
			if (globs->gend[gi - 1] != '\\' && globs->gend[gi] && ft_strchr("*?[", globs->gend[gi]))
				return (ft_nextglob(globs, dname, ri, gi));
			if (dname[ri] == '\0')
				return (1);
			else
				gi = tempj;
		}
		if (globs->gend[gi - 1] != '\\' && globs->gend[gi] && ft_strchr("*?[", globs->gend[gi]))
			return (ft_nextglob(globs, dname, ri, gi));
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
	if (globs->gsta[0] != '.' && dname[0] == '.')
		return (0);
	while (globs->gend[gi] == '*')
		gi++;
	if (globs->gend[gi] == '\0' && dname[ri] == '\0')
		return (1);
	while (dname[ri])
	{
		while (globs->gend[gi] == '*')
			gi++;
		if (dname[ri] == globs->gend[gi] || globs->gend[0] == '\0')
		{
			if (globs->gend[0] == '\0')
				return (1);
			while (globs->gend[gi] == '\\' || (dname[ri] && globs->gend[gi] && dname[ri] == globs->gend[gi]))
			{
				if (globs->gend[gi] != '\\')
					ri++;
				gi++;
			}
			if (dname[ri] == '\0' && globs->gend[gi] == '\0')
				return (1);
			if (globs->gend[gi - 1] != '\\' && globs->gend[gi] && ft_strchr("*?[", globs->gend[gi]))
			{
				ret = ft_nextglob(globs, dname, ri, gi);
				if (ret == 1)
					return (ret);
				ri++;
				gi = 0;
			}
			else
			{
				ri++;
				gi = 0;
			}
		}
		else if (ft_strchr("*?[", globs->gend[gi]))
		{
			if (ft_nextglob(globs, dname, ri, gi))
				return (ret);
			temp++;
			ri = temp;
		}
		else
		{
			temp++;
			ri = temp;
		}
	}
	return (0);
}
