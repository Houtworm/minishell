/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   globs.c                                         |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: houtworm <codam@houtworm.net>              //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/09/03 09:12:54 by houtworm     /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/09/03 21:54:23 by houtworm     \___)=(___/                 */
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
	return (globs);
}

int	ft_parseglobs(t_cmds *cmd)
{
	t_globs			*globs;
	int				i;
	int				j;
	int				k;
	int				l;

	i = 0;
	j = 0;
	k = 0;
	l = 0;
	globs = ft_initglobstruct(cmd->pipeline);
	while (globs->pipeline[i + j + k + l])
	{
		k = 0;
		if (globs->pipeline[i + j] == '\'')
		{
			j++;
			while (globs->pipeline[i + j] != '\'' && globs->pipeline[i + j])
			{
				globs->gstart[j] = globs->pipeline[i + j];
				j++;
			}
			j++;
		}
		if (globs->pipeline[i + j] == '\"')
		{
			j++;
			while (globs->pipeline[i + j] != '\"' && globs->pipeline[i + j])
			{
				globs->gstart[j] = globs->pipeline[i + j];
				j++;
			}
			j++;
		}
		if (globs->pipeline[i + j] == ' ')
		{
			i = i + j + 1;
			j = 0;
		}
		if (globs->pipeline[i + j] == '*')
		{
			globs->period = 0;
			if (globs->pipeline[i + j - 1] == '.')
				globs->period = 1;
			globs->gstart[j] = '\0';
			j++;
			while (globs->pipeline[i + j + k] && !ft_strchr(" /", globs->pipeline[i + j + k]))
			{
				globs->gend[k] = globs->pipeline[i + j + k];
				k++;
			}
			globs->gend[k] = '\0';
			if (globs->pipeline[i + j + k] == '/')
			{
				l = 0;
				while (globs->pipeline[i + j + k + l] && globs->pipeline[i + j + k + l] != ' ')
				{
					globs->subdir[l] = globs->pipeline[i + j + k + l];
					l++;
				}
				globs->subdir[l] = '\0';
			}
			/*j++;*/
			globs->start = ft_substr(globs->pipeline, 0, i);
			ft_parsewildcard(*cmd, globs);
			cmd->pipeline = ft_vastrjoin(3, globs->start, globs->matches, &cmd->pipeline[i + j + k + l]);
		}
		globs->gstart[j] = globs->pipeline[i + j + k];
		j++;
	}
	return (0);
}
