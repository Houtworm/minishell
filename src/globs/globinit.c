/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   globinit.c                                      |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: houtworm <codam@houtworm.net>              //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/09/20 03:32:43 by houtworm     /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/10/10 00:47:00 by houtworm     \___)=(___/                 */
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
	globs->subdir = ft_calloc(ft_strlen(globs->pipeline), 128);
	while (globs->gend[k]) // looping trough the globend for subdirectories
	{
		if (globs->gend[k] == '/') // if we find a / it means we found a subdir
		{
			globs->gend[k] = '\0'; // here we set the endpoint for the globend as subdirectories shouldn't be there
			if (globs->gend[k + 1] == '\0')
				break;
			globs->subdir[i] = ft_calloc(ft_strlen(globs->gend + 1), 8); // malloc
			globs->subdir[i][0] = '/'; // subdirs start with a / for easy joining
			j = 1;
			while(globs->gend[k + j] && globs->gend[k + j] != '/') // we just copy untill we find a next slash
			{
				globs->subdir[i][j] = globs->gend[k + j]; // copy copy copy
				j++;
			}
			globs->subdir[i][j] = '\0'; // set the end of the subdir
			k = k + j; // adding the counters
			i++; // next subdir.
		}
		else // no more subdirs to parse
			k++;
	}
	globs->subdir[i] = NULL;
}

int	ft_getparent(t_globs *globs)
{
	int	i;
	int	j;

	if (ft_strchr(globs->gstart, '/')) // checking if there is a / in the globstart
	{
		i = ft_strlen(globs->gstart); // set endposition
		while (globs->gstart[i - 1] != '/') // while we are not at the last slash
			i--;
		j = 0;
		while (j < i) // while we are not at the last slash we copy over the globstart from the beginning.
		{
			/*printf("getparent copy over %c\n", globs->gstart[j]);*/
			globs->pardir[j] = globs->gstart[j];
			j++;
		}
		globs->pardir[j] = '\0'; // set the \0 for the parentdir
		j = 0;
		while (globs->gstart[i]) // while there are characters after the last slash
		{
			globs->gstart[j] = globs->gstart[i]; // copy over the characters after the slash to the beginning
			i++;
			j++;
		}
		globs->gstart[j] = '\0'; // making sure globstart stops here
	}
	return (0);
}

int	ft_getglob(t_globs *globs, int startpos)
{ // copies the start of the glob and the end of the glob to the struct.
	int 	endpos;
	char	quote;

	endpos = 0;
	globs->gstart[startpos] = '\0'; // set the \0 at the end
	startpos++;
	while (globs->pipeline[globs->linecount + startpos + endpos] && globs->pipeline[globs->linecount + startpos + endpos] != ' ')
	{ // while pipeline and pipeline is not ' '
	  	if (ft_strchr("\'\"", globs->pipeline[globs->linecount + startpos + endpos]))
		{
			quote = globs->pipeline[globs->linecount + startpos + endpos];
			globs->gend[endpos] = globs->pipeline[globs->linecount + startpos + endpos]; // copy it over
			endpos++;
			while (globs->pipeline[globs->linecount + startpos + endpos] != quote)
			{
				globs->gend[endpos] = globs->pipeline[globs->linecount + startpos + endpos]; // copy it over
				endpos++;
			}
		}
		globs->gend[endpos] = globs->pipeline[globs->linecount + startpos + endpos]; // copy it over
		endpos++;
	}
	globs->gend[endpos] = '\0'; // set the \0 for the end glob
	free(globs->start);
	globs->start = ft_substr(globs->pipeline, 0, globs->linecount); // copy globstart
	/*printf("getglob globstart: \n%s\n", globs->start);*/
	free(globs->end);
	globs->end = ft_strdup(&globs->pipeline[globs->linecount + startpos + endpos]); // copy globend
	return (endpos);
}

t_globs *ft_initglobstruct(char *pipeline)
{
	t_globs			*globs;
	int				linelenght;

	linelenght = ft_strlen(pipeline);
	globs = ft_calloc(linelenght , 128);
	globs->gstart = ft_calloc(linelenght, 8);
	globs->gend = ft_calloc(linelenght, 8);
	globs->start = ft_calloc(linelenght, 8);
	globs->end = ft_calloc(linelenght, 8);
	globs->glob = ft_calloc(linelenght, 8);
	globs->subdir = ft_calloc(linelenght, 128);
	globs->tempsubdir = ft_calloc(linelenght, 128);
	globs->pardir = ft_calloc(linelenght, 8);
	globs->anyof = ft_calloc(linelenght, 8);
	globs->matches = ft_calloc(linelenght, 4096);
	globs->pipeline = ft_strdup(pipeline);
	globs->linecount = 0;
	globs->matchcount = 0;
	return (globs);
}
