/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   initsubdir.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: houtworm <codam@houtworm.net>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/20 18:50:08 by houtworm      #+#    #+#                 */
/*   Updated: 2023/10/21 15:31:01 by djonker       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_cleansubdir(t_globs *globs)
{
	int		olddir;
	int		newdir;
	int		oldcount;
	int		newcount;

	olddir = 0;
	newdir = 0;
	while (globs->sdir[olddir])
	{
		while (globs->sdir[olddir] && globs->sdir[olddir][0] == '/' && globs->sdir[olddir][1] == '\0')
			olddir++;
		if (!globs->sdir[olddir])
		{
			newdir++;
			break ;
		}
		oldcount = 0;
		newcount = 0;
		while (globs->sdir[olddir][oldcount])
		{
			if (globs->sdir[olddir][oldcount] == '/')
			{
				globs->sdir[newdir][newcount] = globs->sdir[olddir][oldcount];
				newcount++;
				oldcount++;
				while (globs->sdir[olddir][oldcount] == '/')
					oldcount++;
				while (globs->sdir[olddir][oldcount] && globs->sdir[olddir][oldcount] != '/')
				{
					globs->sdir[newdir][newcount] = globs->sdir[olddir][oldcount];
					newcount++;
					oldcount++;
				}
			}
			globs->sdir[newdir][newcount] = globs->sdir[olddir][oldcount];
			oldcount++;
			newcount++;
		}
		globs->sdir[newdir][newcount] = '\0';
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

void	ft_removequotesfromsubdir(t_globs *globs)
{
	int		i;
	int		j;
	int		k;
	char	quote;

	i = 0;
	while (globs->sdir[i])
	{
		j = 0;
		k = 0;
		while (globs->sdir[i][j])
		{
			if (ft_strchr("\'\"", globs->sdir[i][j]))
			{
				quote = globs->sdir[i][j];
				j++;
				while (globs->sdir[i][j] != quote)
				{
					if (ft_strchr("*?[", globs->sdir[i][j]))
					{
						globs->sdir[i][k] = '\\';
						k++;
					}
					globs->sdir[i][k] = globs->sdir[i][j];
					j++;
					k++;
				}
				j++;
			}
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
