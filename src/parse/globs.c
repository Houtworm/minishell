/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   globs.c                                         |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: houtworm <codam@houtworm.net>              //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/09/03 09:12:54 by houtworm     /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/09/04 02:17:42 by houtworm     \___)=(___/                 */
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

int	ft_skipbutcopy(t_globs *globs, int count)
{
	int		ista;

	ista = 0;
	if (globs->pipeline[count + ista] == '\'')
	{
		ista++;
		while (globs->pipeline[count + ista] != '\'' && globs->pipeline[count + ista])
		{
			globs->gstart[ista] = globs->pipeline[count + ista];
			ista++;
		}
		ista++;
	}
	if (globs->pipeline[count + ista] == '\"')
	{
		ista++;
		while (globs->pipeline[count + ista] != '\"' && globs->pipeline[count + ista])
		{
			globs->gstart[ista] = globs->pipeline[count + ista];
			ista++;
		}
		ista++;
	}
	return (count + ista);
}

int	ft_parseglobs(t_cmds *cmd)
{
	t_globs			*globs;
	int				ipipe;
	int				igend;
	int				igbeg;
	int				i;

	ipipe = 0;
	igbeg = 0;
	igend = 0;
	i = 0;
	globs = ft_initglobstruct(cmd->pipeline);
	while (globs->pipeline[ipipe + igbeg + igend + i])
	{
		igend = 0;
		if (globs->pipeline[ipipe + igbeg] == '\'')
		{
			igbeg++;
			while (globs->pipeline[ipipe + igbeg] != '\'' && globs->pipeline[ipipe + igbeg])
			{
				globs->gstart[igbeg] = globs->pipeline[ipipe + igbeg];
				igbeg++;
			}
			igbeg++;
		}
		if (globs->pipeline[ipipe + igbeg] == '\"')
		{
			igbeg++;
			while (globs->pipeline[ipipe + igbeg] != '\"' && globs->pipeline[ipipe + igbeg])
			{
				globs->gstart[igbeg] = globs->pipeline[ipipe + igbeg];
				igbeg++;
			}
			igbeg++;
		}
		if (globs->pipeline[ipipe + igbeg] == ' ')
		{
			ipipe = ipipe + igbeg + 1;
			igbeg = 0;
		}
		if (globs->pipeline[ipipe + igbeg] == '*')
		{
			globs->period = 0;
			if (globs->pipeline[ipipe + igbeg - 1] == '.')
				globs->period = 1;
			globs->gstart[igbeg] = '\0';
			igbeg++;
			while (globs->pipeline[ipipe + igbeg + igend] && !ft_strchr(" /", globs->pipeline[ipipe + igbeg + igend]))
			{
				globs->gend[igend] = globs->pipeline[ipipe + igbeg + igend];
				igend++;
			}
			globs->gend[igend] = '\0';
			if (globs->pipeline[ipipe + igbeg + igend] == '/')
			{
				i = 0;
				while (globs->pipeline[ipipe + igbeg + igend + i] && globs->pipeline[ipipe + igbeg + igend + i] != ' ')
				{
					globs->subdir[i] = globs->pipeline[ipipe + igbeg + igend + i];
					i++;
				}
				globs->subdir[i] = '\0';
			}
			/*j++;*/
			globs->start = ft_substr(globs->pipeline, 0, ipipe);
			ft_parsewildcard(*cmd, globs);
			cmd->pipeline = ft_vastrjoin(3, globs->start, globs->matches, &cmd->pipeline[ipipe + igbeg + igend + i]);
		}
		globs->gstart[igbeg] = globs->pipeline[ipipe + igbeg + igend];
		igbeg++;
	}
	return (0);
}

/*int	ft_parseglobs(t_cmds *cmd)*/
/*{*/
	/*t_globs			*globs;*/
	/*int				ipipe;*/
	/*int				igend;*/
	/*int				igbeg;*/
	/*int				i;*/

	/*ipipe = 0;*/
	/*igbeg = 0;*/
	/*igend = 0;*/
	/*i = 0;*/
	/*globs = ft_initglobstruct(cmd->pipeline);*/
	/*while (globs->pipeline[ipipe + igbeg + igend + i])*/
	/*{*/
		/*igend = 0;*/
		/*if (globs->pipeline[ipipe + igbeg] == '\'')*/
		/*{*/
			/*igbeg++;*/
			/*while (globs->pipeline[ipipe + igbeg] != '\'' && globs->pipeline[ipipe + igbeg])*/
			/*{*/
				/*globs->gstart[igbeg] = globs->pipeline[ipipe + igbeg];*/
				/*igbeg++;*/
			/*}*/
			/*igbeg++;*/
		/*}*/
		/*if (globs->pipeline[ipipe + igbeg] == '\"')*/
		/*{*/
			/*igbeg++;*/
			/*while (globs->pipeline[ipipe + igbeg] != '\"' && globs->pipeline[ipipe + igbeg])*/
			/*{*/
				/*globs->gstart[igbeg] = globs->pipeline[ipipe + igbeg];*/
				/*igbeg++;*/
			/*}*/
			/*igbeg++;*/
		/*}*/
		/*if (globs->pipeline[ipipe + igbeg] == ' ')*/
		/*{*/
			/*ipipe = ipipe + igbeg + 1;*/
			/*igbeg = 0;*/
		/*}*/
		/*if (globs->pipeline[ipipe + igbeg] == '*')*/
		/*{*/
			/*globs->period = 0;*/
			/*if (globs->pipeline[ipipe + igbeg - 1] == '.')*/
				/*globs->period = 1;*/
			/*globs->gstart[igbeg] = '\0';*/
			/*igbeg++;*/
			/*while (globs->pipeline[ipipe + igbeg + igend] && !ft_strchr(" /", globs->pipeline[ipipe + igbeg + igend]))*/
			/*{*/
				/*globs->gend[igend] = globs->pipeline[ipipe + igbeg + igend];*/
				/*igend++;*/
			/*}*/
			/*globs->gend[igend] = '\0';*/
			/*if (globs->pipeline[ipipe + igbeg + igend] == '/')*/
			/*{*/
				/*i = 0;*/
				/*while (globs->pipeline[ipipe + igbeg + igend + i] && globs->pipeline[ipipe + igbeg + igend + i] != ' ')*/
				/*{*/
					/*globs->subdir[i] = globs->pipeline[ipipe + igbeg + igend + i];*/
					/*i++;*/
				/*}*/
				/*globs->subdir[i] = '\0';*/
			/*}*/
			/*globs->start = ft_substr(globs->pipeline, 0, ipipe);*/
			/*ft_parsewildcard(*cmd, globs);*/
			/*cmd->pipeline = ft_vastrjoin(3, globs->start, globs->matches, &cmd->pipeline[ipipe + igbeg + igend + i]);*/
		/*}*/
		/*globs->gstart[igbeg] = globs->pipeline[ipipe + igbeg + igend];*/
		/*igbeg++;*/
	/*}*/
	/*return (0);*/
/*}*/
