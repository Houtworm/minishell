/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   initsubdir.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: houtworm <codam@houtworm.net>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/20 18:50:08 by houtworm      #+#    #+#                 */
/*   Updated: 2023/10/21 17:04:19 by djonker       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_newsubdir(t_globs *globs, int oldd, int newdir, int oldc)
{
	int	newcount;

	newcount = 0;
	while (globs->sdir[oldd][oldc])
	{
		if (globs->sdir[oldd][oldc] == '/')
		{
			globs->sdir[newdir][newcount] = globs->sdir[oldd][oldc];
			newcount++;
			oldc++;
			while (globs->sdir[oldd][oldc] == '/')
				oldc++;
			while (globs->sdir[oldd][oldc] && globs->sdir[oldd][oldc] != '/')
			{
				globs->sdir[newdir][newcount] = globs->sdir[oldd][oldc];
				newcount++;
				oldc++;
			}
		}
		globs->sdir[newdir][newcount] = globs->sdir[oldd][oldc];
		oldc++;
		newcount++;
	}
	globs->sdir[newdir][newcount] = '\0';
}

void	ft_cleansubdir(t_globs *globs)
{
	int		olddir;
	int		newdir;

	olddir = 0;
	newdir = 0;
	while (globs->sdir[olddir])
	{
		while (globs->sdir[olddir] && globs->sdir[olddir][0] == '/' && \
				globs->sdir[olddir][1] == '\0')
			olddir++;
		if (!globs->sdir[olddir])
		{
			newdir++;
			break ;
		}
		ft_newsubdir(globs, olddir, newdir, 0);
		newdir++;
		olddir++;
	}
	while (newdir < olddir)
	{
		free(globs->sdir[newdir]);
		globs->sdir[newdir] = NULL;
		newdir++;
	}
}

void	ft_subdirfoundquote(t_globs *globs, int i, int *j, int *k)
{
	char	quote;

	quote = globs->sdir[i][*j];
	(*j)++;
	while (globs->sdir[i][*j] != quote)
	{
		if (ft_strchr("*?[", globs->sdir[i][*j]))
		{
			globs->sdir[i][*k] = '\\';
			(*k)++;
		}
		globs->sdir[i][*k] = globs->sdir[i][*j];
		(*j)++;
		(*k)++;
	}
	(*j)++;
}

void	ft_removequotesfromsubdir(t_globs *globs)
{
	int		i;
	int		j;
	int		k;

	i = 0;
	while (globs->sdir[i])
	{
		j = 0;
		k = 0;
		while (globs->sdir[i][j])
		{
			if (ft_strchr("\'\"", globs->sdir[i][j]))
				ft_subdirfoundquote(globs, i, &j, &k);
			if (globs->sdir[i][j])
			{
				globs->sdir[i][k] = globs->sdir[i][j];
				k++;
				j++;
			}
		}
		globs->sdir[i][k] = '\0';
		i++;
	}
}

void	ft_getsubdir(t_globs *globs, int i, int j, int k)
{
	ft_frearr(globs->sdir);
	globs->sdir = ft_calloc(ft_strlen(globs->line), 128);
	while (globs->gend[k])
	{
		if (globs->gend[k] == '/')
		{
			globs->gend[k] = '\0';
			globs->sdir[i] = ft_calloc(500, 8);
			globs->sdir[i][0] = '/';
			j = 1;
			while (globs->gend[k + j] && globs->gend[k + j] != '/')
			{
				globs->sdir[i][j] = globs->gend[k + j];
				j++;
			}
			globs->sdir[i][j] = '\0';
			k = k + j;
			i++;
		}
		else
			k++;
	}
	globs->sdir[i] = NULL;
}
