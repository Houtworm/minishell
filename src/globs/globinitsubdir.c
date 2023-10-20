/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   globinitsub.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: houtworm <codam@houtworm.net>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/20 18:50:08 by houtworm      #+#    #+#                 */
/*   Updated: 2023/10/20 18:50:09 by houtworm      ########   odam.nl         */
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
	while (globs->subdir[olddir])
	{
		while (globs->subdir[olddir] && globs->subdir[olddir][0] == '/' && globs->subdir[olddir][1] == '\0')
			olddir++;
		if (!globs->subdir[olddir])
		{
			newdir++;
			break ;
		}
		oldcount = 0;
		newcount = 0;
		while (globs->subdir[olddir][oldcount])
		{
			if (globs->subdir[olddir][oldcount] == '/')
			{
				globs->subdir[newdir][newcount] = globs->subdir[olddir][oldcount];
				newcount++;
				oldcount++;
				while (globs->subdir[olddir][oldcount] == '/')
					oldcount++;
				while (globs->subdir[olddir][oldcount] && globs->subdir[olddir][oldcount] != '/')
				{
					globs->subdir[newdir][newcount] = globs->subdir[olddir][oldcount];
					newcount++;
					oldcount++;
				}
			}
			globs->subdir[newdir][newcount] = globs->subdir[olddir][oldcount];
			oldcount++;
			newcount++;
		}
		globs->subdir[newdir][newcount] = '\0';
		newdir++;
		olddir++;
	}
	while (newdir < olddir)
	{
		free(globs->subdir[newdir]);
		globs->subdir[newdir] = NULL;
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
	while (globs->subdir[i])
	{
		j = 0;
		k = 0;
		while (globs->subdir[i][j])
		{
			if (ft_strchr("\'\"", globs->subdir[i][j]))
			{
				quote = globs->subdir[i][j];
				j++;
				while (globs->subdir[i][j] != quote)
				{
					if (ft_strchr("*?[", globs->subdir[i][j]))
					{
						globs->subdir[i][k] = '\\';
						k++;
					}
					globs->subdir[i][k] = globs->subdir[i][j];
					j++;
					k++;
				}
				j++;
			}
			if (globs->subdir[i][j])
			{
				globs->subdir[i][k] = globs->subdir[i][j];
				k++;
				j++;
			}
		}
		globs->subdir[i][k] = '\0';
		i++;
	}
}

void	ft_getsubdir(t_globs *globs)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	k = 0;
	ft_frearr(globs->subdir);
	globs->subdir = ft_calloc(ft_strlen(globs->line), 128);
	while (globs->gend[k])
	{
		if (globs->gend[k] == '/')
		{
			globs->gend[k] = '\0';
			globs->subdir[i] = ft_calloc(500, 8);
			globs->subdir[i][0] = '/';
			j = 1;
			while (globs->gend[k + j] && globs->gend[k + j] != '/')
			{
				globs->subdir[i][j] = globs->gend[k + j];
				j++;
			}
			globs->subdir[i][j] = '\0';
			k = k + j;
			i++;
		}
		else
			k++;
	}
	globs->subdir[i] = NULL;
}

