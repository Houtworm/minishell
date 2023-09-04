/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   globs.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: houtworm <codam@houtworm.net>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/03 09:12:54 by houtworm      #+#    #+#                 */
/*   Updated: 2023/09/04 09:27:18 by yitoh         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_globs *ft_initglobstruct(char *pipeline)
{
	t_globs			*globs;
	int				linelenght;

	linelenght = ft_strlen(pipeline);
	globs = ft_calloc(linelenght , 128);
	globs->gstart = ft_calloc(linelenght, 8);
	globs->gend = ft_calloc(linelenght, 8);
	globs->start = ft_calloc(linelenght, 8);
	globs->glob = ft_calloc(linelenght, 8);
	globs->end = ft_calloc(linelenght, 8);
	globs->subdir = ft_calloc(linelenght, 8);
	globs->pardir = ft_calloc(linelenght, 8);
	globs->matches = ft_calloc(linelenght, 8);
	globs->pipeline = ft_strdup(pipeline);
	globs->linecount = 0;
	return (globs);
}

int	ft_skipbutcopy(t_globs *globs, int startpos)
{
	if (globs->pipeline[globs->linecount + startpos] == '\'')
	{
		startpos++;
		while (globs->pipeline[globs->linecount + startpos] != '\'' && globs->pipeline[globs->linecount + startpos])
		{
			globs->gstart[startpos] = globs->pipeline[globs->linecount + startpos];
			startpos++;
		}
		startpos++;
	}
	if (globs->pipeline[globs->linecount + startpos] == '\"')
	{
		startpos++;
		while (globs->pipeline[globs->linecount + startpos] != '\"' && globs->pipeline[globs->linecount + startpos])
		{
			globs->gstart[startpos] = globs->pipeline[globs->linecount + startpos];
			startpos++;
		}
		startpos++;
	}
	globs->linecount = globs->linecount + startpos;
	return (startpos);
}

int	ft_wildcardmatch(t_cmds *cmd, t_globs *globs, int startpos)
{
	int endpos;
	int	i;

	endpos = 0;
	globs->period = 0;
	//Yuka added i = 0 to silence the compilation error
	i = 0;
	if (globs->pipeline[globs->linecount + startpos - 1] == '.')
		globs->period = 1;
	globs->gstart[startpos] = '\0';
	startpos++;
	while (globs->pipeline[globs->linecount + startpos + endpos] && !ft_strchr(" /", globs->pipeline[globs->linecount + startpos + endpos]))
	{
		globs->gend[endpos] = globs->pipeline[globs->linecount + startpos + endpos];
		endpos++;
	}
	globs->gend[endpos] = '\0';
	if (globs->pipeline[globs->linecount + startpos + endpos] == '/')
	{
		i = 0;
		while (globs->pipeline[globs->linecount + startpos + endpos + i] && globs->pipeline[globs->linecount + startpos + endpos + i] != ' ')
		{
			globs->subdir[i] = globs->pipeline[globs->linecount + startpos + endpos + i];
			i++;
		}
		globs->subdir[i] = '\0';
	}
	globs->start = ft_substr(globs->pipeline, 0, globs->linecount);
	globs->end = ft_strdup(&cmd->pipeline[globs->linecount + startpos + endpos + i]);
	ft_parsewildcard(*cmd, globs);
	cmd->pipeline = ft_vastrjoin(3, globs->start, globs->matches, globs->end);
	return (endpos);
}

int	ft_parseglobs(t_cmds *cmd)
{
	t_globs			*globs;
	int				startpos;
	int				endpos;

	startpos = 0;
	endpos = 0;
	globs = ft_initglobstruct(cmd->pipeline);
	while (globs->pipeline[globs->linecount + startpos + endpos])
	{
		if (ft_strchr("\'\"", globs->pipeline[globs->linecount]))
			startpos = ft_skipbutcopy(globs, startpos);
		if (globs->pipeline[globs->linecount + startpos] == ' ')
		{
			globs->linecount = globs->linecount + startpos + 1;
			startpos = 0;
		}
		if (globs->pipeline[globs->linecount + startpos] == '*')
		{
			endpos = ft_wildcardmatch(cmd, globs, startpos);
			startpos++;
		}
		globs->gstart[startpos] = globs->pipeline[globs->linecount + startpos + endpos];
		startpos++;
	}
	return (0);
}
