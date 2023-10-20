/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   globinit.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: houtworm <codam@houtworm.net>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/20 03:32:43 by houtworm      #+#    #+#                 */
/*   Updated: 2023/10/20 18:47:00 by houtworm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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
