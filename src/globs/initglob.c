/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   globinit.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: houtworm <codam@houtworm.net>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/20 03:32:43 by houtworm      #+#    #+#                 */
/*   Updated: 2023/10/20 19:08:53 by houtworm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_skipbutcopygstart(t_globs *globs, int startpos)
{
	char	quote;

	if (ft_strchr("\'\"", globs->line[globs->linecount + startpos]))
	{
		quote = globs->line[globs->linecount + startpos];
		globs->gstart[startpos] = globs->line[globs->linecount + startpos];
		startpos++;
		while (globs->line[globs->linecount + startpos] != quote)
		{
			globs->gstart[startpos] = globs->line[globs->linecount + startpos];
			startpos++;
		}
		globs->gstart[startpos] = globs->line[globs->linecount + startpos];
		startpos++;
	}
	return (startpos);
}

void	ft_globmatches(t_globs *globs, char *dname, unsigned char type, char *fullpath)
{
	char	*temp;

	if (globs->subdir[0])
	{
		if (type == DT_DIR)
		{
			temp = ft_vastrjoin(2, fullpath, dname);
			free(globs->tempsubdir[0]);
			globs->tempsubdir[0] = ft_strjoin("/", dname);
			ft_recursivematchsub(globs, temp, dname, 0);
			free(temp);
		}
	}
	else
	{
		temp = ft_vastrjoin(2, globs->pardir, dname);
		ft_addglobmatch(globs, temp);
		free(temp);
	}
}

void	ft_matchtillglob(t_globs *globs, char *dname, char *fullpath, unsigned char type)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (globs->gstart[j + i] == '\\' || (dname[i] && globs->gstart[j + i] == dname[i]))
	{
		if (globs->gstart[i + j] == '\\')
			j++;
		else
			i++;
	}
	if (globs->gstart[j + i] == '\0')
	{
		if (ft_firstglob(globs, dname, i))
		{
			ft_globmatches(globs, dname, type, fullpath);
		}
	}
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
