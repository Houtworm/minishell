/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   globinit.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: houtworm <codam@houtworm.net>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/20 03:32:43 by houtworm      #+#    #+#                 */
/*   Updated: 2023/10/19 06:00:16 by djonker       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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
		while (globs->gstart[i])
		{
			globs->gstart[j] = globs->gstart[i];
			i++;
			j++;
		}
		globs->gstart[j] = '\0';
	}
	return (0);
}

int	ft_getglob(t_globs *globs, int startpos)
{
	int		endpos;
	char	quote;

	endpos = 0;
	globs->gstart[startpos] = '\0';
	startpos++;
	while (globs->line[globs->linecount + startpos + endpos] && globs->line[globs->linecount + startpos + endpos] != ' ')
	{
		if (ft_strchr("\'\"", globs->line[globs->linecount + startpos + endpos]))
		{
			quote = globs->line[globs->linecount + startpos + endpos];
			globs->gend[endpos] = globs->line[globs->linecount + startpos + endpos];
			endpos++;
			while (globs->line[globs->linecount + startpos + endpos] != quote)
			{
				globs->gend[endpos] = globs->line[globs->linecount + startpos + endpos];
				endpos++;
			}
			globs->gend[endpos] = globs->line[globs->linecount + startpos + endpos];
			endpos++;
		}
		else
		{
			globs->gend[endpos] = globs->line[globs->linecount + startpos + endpos];
			endpos++;
		}
	}
	globs->gend[endpos] = '\0';
	free(globs->start);
	globs->start = ft_substr(globs->line, 0, globs->linecount);
	free(globs->end);
	globs->end = ft_strdup(&globs->line[globs->linecount + startpos + endpos]);
	return (endpos);
}

t_globs	*ft_initglobstruct(char *line)
{
	t_globs			*globs;
	int				linelenght;

	linelenght = ft_strlen(line);
	globs = ft_calloc(linelenght, 128);
	globs->gstart = ft_calloc(linelenght, 8);
	globs->gend = ft_calloc(500, 8);
	globs->start = ft_calloc(linelenght, 8);
	globs->end = ft_calloc(linelenght, 8);
	globs->glob = ft_calloc(linelenght, 8);
	globs->backup = ft_calloc(linelenght, 8);
	globs->subdir = ft_calloc(linelenght, 128);
	globs->tempsubdir = ft_calloc(linelenght, 128);
	globs->pardir = ft_calloc(linelenght * 2, 8);
	globs->anyof = ft_calloc(linelenght, 8);
	globs->matches = ft_calloc(linelenght, 4096);
	globs->line = ft_strdup(line);
	globs->linecount = 0;
	globs->matchcount = 0;
	return (globs);
}
