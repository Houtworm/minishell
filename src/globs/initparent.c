/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   initparent.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: houtworm <codam@houtworm.net>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/20 18:49:57 by houtworm      #+#    #+#                 */
/*   Updated: 2023/10/21 15:34:02 by djonker       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_cleanpardir(t_globs *globs, int oldcount, int newcount)
{
	while (globs->pdir[oldcount])
	{
		if (globs->pdir[oldcount] == '/')
		{
			oldcount++;
			newcount = oldcount;
			while (globs->pdir[oldcount] == '/')
				oldcount++;
			if (oldcount > newcount)
			{
				while (globs->pdir[oldcount] && globs->pdir[oldcount] != '/')
				{
					globs->pdir[newcount] = globs->pdir[oldcount];
					oldcount++;
					newcount++;
				}
			}
		}
		oldcount++;
	}
	globs->pdir[newcount] = '\0';
}

void	ft_removequotesfrompardir(t_globs *globs, int i, int j)
{
	char	quote;

	while (globs->pdir[i + j])
	{
		if (ft_strchr("\'\"", globs->pdir[i + j]))
		{
			quote = globs->pdir[i + j];
			i++;
			while (globs->pdir[i + j] != quote)
			{
				globs->pdir[j] = globs->pdir[i + j];
				j++;
			}
			i++;
		}
		while (globs->pdir[i + j] && !ft_strchr("\'\"", globs->pdir[i + j]))
		{
			globs->pdir[j] = globs->pdir[i + j];
			j++;
		}
	}
	globs->pdir[j] = '\0';
}

int	ft_getparent(t_globs *globs, int i, int j)
{
	if (ft_strchr(globs->gsta, '/'))
	{
		i = ft_strlen(globs->gsta);
		while (globs->gsta[i - 1] != '/')
			i--;
		j = 0;
		while (j < i)
		{
			globs->pdir[j] = globs->gsta[j];
			j++;
		}
		globs->pdir[j] = '\0';
		j = 0;
		while (globs->gsta[i + j])
		{
			globs->gsta[j] = globs->gsta[i + j];
			j++;
		}
		globs->gsta[j] = '\0';
	}
	return (0);
}
