/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   globs.c                                         |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: houtworm <codam@houtworm.net>              //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/09/03 09:12:54 by houtworm     /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/09/06 11:49:19 by djonker      \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_skipbutcopygstart(t_globs *globs, int startpos)
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

void	ft_checkglobmatch(t_globs *globs, char *dir)
{	// should check if it actually matches with parent and sub dir
	/*char	*temp;*/

	globs->pardir = ft_strdup(dir);
	globs->matches = ft_vastrjoin(4, globs->matches, dir, globs->subdir, " ");
}

void	ft_parsewildcard(t_cmds cmd, t_globs *globs)
{
	DIR				*dir;
	struct dirent	*dirents;
	char			*curdir;
	int				i;
	int				j;

	curdir = ft_getpwd(cmd.envp, 1);
	dir = opendir(curdir); // needs to run for every sub directory.
	while ((dirents = readdir(dir))) // everytime this is called we move to the next file in directory
	{
		if (!ft_strncmp(dirents->d_name, globs->gstart, ft_strlen(globs->gstart))) // if start of glob matches
		{
			i = ft_strlen(globs->gend);
			j = ft_strlen(dirents->d_name);
			while (i && j && globs->gend[i] == dirents->d_name[j]) //while characters match from the end
			{
				i--;
				j--;
			}
			if (i == 0 && globs->gend[i] == dirents->d_name[j])// if first character of glob end matches
			{
				if (globs->period == 1)
					if (dirents->d_name[0] == '.')
						globs->matches = ft_vastrjoin(4, globs->matches, dirents->d_name, globs->subdir, " ");
				if (globs->period == 0)
					if (dirents->d_name[0] != '.')
						globs->matches = ft_vastrjoin(4, globs->matches, dirents->d_name, globs->subdir, " ");
			}
		}
	}
	closedir(dir);
	if (!globs->matches)
		globs->matches = ft_vastrjoin(4, globs->gstart, "*", globs->gend);
}

int	ft_parseglob(t_cmds *cmd, t_globs *globs)
{
	ft_parsewildcard(*cmd, globs);
	return (0);
}

int	ft_getglob(t_globs *globs, int startpos) //defines the start of pipe, the glob the subdir and the rest
{
	int endpos;
	int	i;

	endpos = 0;
	i = 0;
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
		while (globs->pipeline[globs->linecount + startpos + endpos + i] && globs->pipeline[globs->linecount + startpos + endpos + i] != ' ')
		{
			globs->subdir[i] = globs->pipeline[globs->linecount + startpos + endpos + i];
			i++;
		}
		globs->subdir[i] = '\0';
	}
	globs->start = ft_substr(globs->pipeline, 0, globs->linecount);
	globs->end = ft_strdup(&globs->pipeline[globs->linecount + startpos + endpos + i]);
	return (endpos);
}

int	ft_newpipeline(t_globs *globs)
{
	globs->pipeline = ft_vastrjoin(3, globs->start, globs->matches, globs->end);
	globs->linecount = globs->linecount + ft_strlen(globs->matches);
	return (0);
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

void	ft_globlooper(t_globs *globs, t_cmds *cmd, int startpos)
{
	while (globs->pipeline[globs->linecount + startpos])
	{
		if (ft_strchr("\'\"", globs->pipeline[globs->linecount]))
			startpos = ft_skipbutcopygstart(globs, startpos);
		if (globs->pipeline[globs->linecount + startpos] == ' ')
		{
			globs->linecount = globs->linecount + startpos + 1;
			startpos = 0;
		}
		if (ft_strchr("*?[", globs->pipeline[globs->linecount + startpos]))
		{
			ft_getglob(globs, startpos); //extracts the glob, puts all characters before and after in 2 seperate strings
			ft_getparent(globs); //looks in the glob if it contains any extra directories above or below the glob
			ft_parseglob(cmd, globs); //parses the glob character by character
			ft_newpipeline(globs); //constructs the new pipeline, sets the new position in the pipeline right after the parsed glob
			if (cmd->debug)
				ft_printglobs(*globs, "end of parsewildcard");
			startpos++;
		}
		else
		{
			globs->gstart[startpos] = globs->pipeline[globs->linecount + startpos];
			startpos++;
		}
	}
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
	globs->glob = ft_calloc(linelenght, 8);
	globs->end = ft_calloc(linelenght, 8);
	globs->subdir = ft_calloc(linelenght, 8);
	globs->pardir = ft_calloc(linelenght, 8);
	globs->matches = ft_calloc(linelenght, 8);
	globs->pipeline = ft_strdup(pipeline);
	globs->linecount = 0;
	return (globs);
}

int	ft_parseglobs(t_cmds *cmd) //should initialize the globbing
{
	t_globs			*globs;

	globs = ft_initglobstruct(cmd->pipeline);
	if (ft_checkoutquote(cmd->pipeline, '*', 2) >= 0)
		ft_globlooper(globs, cmd, 0);
	if (ft_checkoutquote(cmd->pipeline, '?', 2) >= 0)
		ft_globlooper(globs, cmd, 0);
	if (ft_checkoutquote(cmd->pipeline, '[', 2) >= 0)
		ft_globlooper(globs, cmd, 0);
	cmd->pipeline = ft_strdup(globs->pipeline);
	// free globs here
	return (0);
}

/*int	ft_skipbutcopy(t_globs *globs, int startpos)*/
/*{*/
	/*if (globs->pipeline[globs->linecount + startpos] == '\'')*/
	/*{*/
		/*startpos++;*/
		/*while (globs->pipeline[globs->linecount + startpos] != '\'' && globs->pipeline[globs->linecount + startpos])*/
		/*{*/
			/*globs->gstart[startpos] = globs->pipeline[globs->linecount + startpos];*/
			/*startpos++;*/
		/*}*/
		/*startpos++;*/
	/*}*/
	/*if (globs->pipeline[globs->linecount + startpos] == '\"')*/
	/*{*/
		/*startpos++;*/
		/*while (globs->pipeline[globs->linecount + startpos] != '\"' && globs->pipeline[globs->linecount + startpos])*/
		/*{*/
			/*globs->gstart[startpos] = globs->pipeline[globs->linecount + startpos];*/
			/*startpos++;*/
		/*}*/
		/*startpos++;*/
	/*}*/
	/*globs->linecount = globs->linecount + startpos;*/
	/*return (startpos);*/
/*}*/

/*int	ft_wildcardmatch(t_cmds *cmd, t_globs *globs, int startpos)*/
/*{*/
	/*int endpos;*/
	/*int	i;*/

	/*endpos = 0;*/
	/*globs->period = 0;*/
	/*i = 0;*/
	/*if (globs->pipeline[globs->linecount + startpos - 1] == '.')*/
		/*globs->period = 1;*/
	/*globs->gstart[startpos] = '\0';*/
	/*startpos++;*/
	/*while (globs->pipeline[globs->linecount + startpos + endpos] && !ft_strchr(" /", globs->pipeline[globs->linecount + startpos + endpos]))*/
	/*{*/
		/*globs->gend[endpos] = globs->pipeline[globs->linecount + startpos + endpos];*/
		/*endpos++;*/
	/*}*/
	/*globs->gend[endpos] = '\0';*/
	/*if (globs->pipeline[globs->linecount + startpos + endpos] == '/')*/
	/*{*/
		/*i = 0;*/
		/*while (globs->pipeline[globs->linecount + startpos + endpos + i] && globs->pipeline[globs->linecount + startpos + endpos + i] != ' ')*/
		/*{*/
			/*globs->subdir[i] = globs->pipeline[globs->linecount + startpos + endpos + i];*/
			/*i++;*/
		/*}*/
		/*globs->subdir[i] = '\0';*/
	/*}*/
	/*globs->start = ft_substr(globs->pipeline, 0, globs->linecount);*/
	/*globs->end = ft_strdup(&cmd->pipeline[globs->linecount + startpos + endpos + i]);*/
	/*ft_parsewildcard(*cmd, globs);*/
	/*cmd->pipeline = ft_vastrjoin(3, globs->start, globs->matches, globs->end);*/
	/*return (endpos);*/
/*}*/

/*int	ft_parseglobs(t_cmds *cmd)*/
/*{*/
	/*t_globs			*globs;*/
	/*int				startpos;*/
	/*int				endpos;*/

	/*startpos = 0;*/
	/*endpos = 0;*/
	/*globs = ft_initglobstruct(cmd->pipeline);*/
	/*while (globs->pipeline[globs->linecount + startpos + endpos])*/
	/*{*/
		/*if (ft_strchr("\'\"", globs->pipeline[globs->linecount]))*/
			/*startpos = ft_skipbutcopy(globs, startpos);*/
		/*if (globs->pipeline[globs->linecount + startpos] == ' ')*/
		/*{*/
			/*globs->linecount = globs->linecount + startpos + 1;*/
			/*startpos = 0;*/
		/*}*/
		/*if (globs->pipeline[globs->linecount + startpos] == '*')*/
		/*{*/
			/*endpos = ft_wildcardmatch(cmd, globs, startpos);*/
			/*startpos++;*/
		/*}*/
		/*globs->gstart[startpos] = globs->pipeline[globs->linecount + startpos + endpos];*/
		/*startpos++;*/
	/*}*/
	/*return (0);*/
/*}*/
