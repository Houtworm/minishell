/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   anyof.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: houtworm <codam@houtworm.net>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/20 00:51:38 by houtworm      #+#    #+#                 */
/*   Updated: 2023/10/20 19:33:49 by houtworm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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
	if (ft_strchr(globs->anyof, match))
	{
		gi++;
		ri++;
	}
	while (globs->gend[gi] == '\\' || (dname[ri] && globs->gend[gi] && dname[ri] == globs->gend[gi]))
	{
		if (globs->gend[gi] == '\\')
			gi++;
		else
		{
			gi++;
			ri++;
		}
	}
	if (globs->gend[gi - 1] != '\\' && globs->gend[gi] && ft_strchr("*?[", globs->gend[gi]))
	{
		return (ft_nextglob(globs, dname, ri, gi));
	}
	if (globs->gend[gi] == '\0' && dname[ri] == '\0')
		return (1);
	return (0);
}

int	ft_firstanyof(t_globs *globs, char *dname, int ri)
{
	int		gi;
	char	*temp;

	gi = 0;
	if (!globs->anyof[0])
	{
		while (globs->gend[gi] && globs->gend[gi] != ']')
		{
			globs->glob[gi + 1] = globs->gend[gi];
			globs->anyof[gi] = globs->gend[gi];
			gi++;
		}
		if (!globs->gend[gi])
			return (0);
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
			return (0);
		globs->anyof[gi] = '\0';
	}
	if (globs->anyof[0] == '\0')
		return (0);
	if (ft_strchr(globs->anyof, dname[ri]))
	{
		gi = 0;
		ri++;
		while (globs->gend[gi] == '\\' || (dname[ri] && globs->gend[gi] && dname[ri] == globs->gend[gi]))
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
	}
	return (0);
}
