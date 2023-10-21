/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   globmatch.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: djonker <codam@houtworm.net>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/21 13:34:34 by djonker       #+#    #+#                 */
/*   Updated: 2023/10/21 14:10:18 by djonker       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_addglobmatch(t_globs *globs, char *match)
{
	globs->matches[globs->matchcount] = ft_strdup(match);
	globs->matchcount++;
}

void	ft_globcleannewline(t_globs *globs, char *temp, int k)
{
	if (globs->matches[0])
	{
		ft_frearr(globs->matches);
		globs->matches = ft_calloc(100, 4096);
		free(globs->line);
		globs->line = ft_vastrjoin(3, globs->start, temp, globs->end);
		ft_frearr(globs->sdir);
		globs->sdir = ft_calloc(100, 128);
		globs->linecount = globs->linecount + k;
	}
	ft_vafree(3, globs->anyof, globs->backup, globs->gend);
	globs->anyof = ft_calloc(100, 8);
	globs->backup = ft_calloc(10000, 8);
	globs->gend = ft_calloc(1000, 8);
	globs->matchcount = 0;
	free(temp);
}

void	ft_newpipefoundmatch(t_globs *globs, char *temp, int i, int k)
{
	int		j;

	while (globs->matches[i])
	{
		j = 0;
		if (ft_isallbyte(globs->matches[i], ' '))
		{
			temp[k] = '\'';
			k++;
		}
		while (globs->matches[i][j])
		{
			temp[k] = globs->matches[i][j];
			j++;
			k++;
		}
		if (ft_isallbyte(globs->matches[i], ' '))
		{
			temp[k] = '\'';
			k++;
		}
		temp[k] = ' ';
		k++;
		i++;
	}
}

int	ft_newpipeline(t_globs *globs)
{
	int		k;
	char	*temp;

	if (!globs->matches[0])
	{
		temp = ft_strdup(globs->backup);
		globs->linecount = globs->linecount + ft_strlen(temp);
	}
	else
	{
		temp = ft_calloc(100000, 8);
		ft_newpipefoundmatch(globs, temp, 0, 0);
		k = ft_strlen(temp);
	}
	ft_globcleannewline(globs, temp, k);
	return (0);
}
