/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   initparent.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: houtworm <codam@houtworm.net>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/20 18:49:57 by houtworm      #+#    #+#                 */
/*   Updated: 2023/10/20 19:21:34 by houtworm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_cleanpardir(t_globs *globs)
{
	int		oldcount;
	int		newcount;

	oldcount = 0;
	newcount = 0;
	while (globs->pardir[oldcount])
	{
		if (globs->pardir[oldcount] == '/')
		{
			oldcount++;
			newcount = oldcount;
			while (globs->pardir[oldcount] == '/')
				oldcount++;
			if (oldcount > newcount)
			{
				while (globs->pardir[oldcount] && globs->pardir[oldcount] != '/')
				{
					globs->pardir[newcount] = globs->pardir[oldcount];
					oldcount++;
					newcount++;
				}
			}
		}
		oldcount++;
	}
	globs->pardir[newcount] = '\0';
}

void	ft_removequotesfrompardir(t_globs *globs)
{
	int		i;
	int		j;
	char	quote;

	i = 0;
	j = 0;
	while (globs->pardir[i])
	{
		if (ft_strchr("\'\"", globs->pardir[i]))
		{
			quote = globs->pardir[i];
			i++;
			while (globs->pardir[i] != quote)
			{
				globs->pardir[j] = globs->pardir[i];
				j++;
				i++;
			}
			i++;
		}
		while (globs->pardir[i] && !ft_strchr("\'\"", globs->pardir[i]))
		{
			globs->pardir[j] = globs->pardir[i];
			j++;
			i++;
		}
	}
	globs->pardir[j] = '\0';
}

int	ft_getparent(t_globs *globs)
{
	int	i;
	int	j;

	if (ft_strchr(globs->gstart, '/'))
	{
		i = ft_strlen(globs->gstart);
		while (globs->gstart[i - 1] != '/')
			i--;
		j = 0;
		while (j < i)
		{
			globs->pardir[j] = globs->gstart[j];
			j++;
		}
		globs->pardir[j] = '\0';
		j = 0;
		while (globs->gstart[i + j])
		{
			globs->gstart[j] = globs->gstart[i + j];
			j++;
		}
		globs->gstart[j] = '\0';
	}
	return (0);
}
