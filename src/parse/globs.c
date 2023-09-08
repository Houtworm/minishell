/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   globs.c                                         |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: houtworm <codam@houtworm.net>              //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/09/03 09:12:54 by houtworm     /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/09/09 01:01:34 by houtworm     \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_skipbutcopygstart(t_globs *globs, int startpos)
{ // copies over characters between quotes so the globs don't get parsed
	if (globs->pipeline[globs->linecount + startpos] == '\'') // if current position is '
	{
		startpos++;
		while (globs->pipeline[globs->linecount + startpos] != '\'' && globs->pipeline[globs->linecount + startpos])
		{ // while current positon is not '
			globs->gstart[startpos] = globs->pipeline[globs->linecount + startpos]; // copy copy copy
			startpos++;
		}
		startpos++;
	}
	if (globs->pipeline[globs->linecount + startpos] == '\"') // if current positon is "
	{
		startpos++;
		while (globs->pipeline[globs->linecount + startpos] != '\"' && globs->pipeline[globs->linecount + startpos])
		{ // while current position is not "
			globs->gstart[startpos] = globs->pipeline[globs->linecount + startpos]; // copy copy copy
			startpos++;
		}
		startpos++;
	}
	globs->linecount = globs->linecount + startpos; // move the line counter accordingly
	return (startpos);
}

int	ft_newpipeline(t_globs *globs)
{ // simply parses the results into the new pipeline
	globs->pipeline = ft_vastrjoin(3, globs->start, globs->matches, globs->end); // new pipeline
	globs->linecount = globs->linecount + ft_strlen(globs->matches); // new linecount
	return (0);
}

void	ft_matchsub(t_globs *globs, char *dname, char *fullpath, unsigned char type)
{ // should match subdirectories recursively
	DIR				*dir;
	struct dirent	*dirents;
	char			*checkdir;
	char			*subdirs;
	int				i;
	int				j;

	i = 0;
	subdirs = NULL;
	checkdir = ft_vastrjoin(2, fullpath, dname); // create the new directory to open
	while (globs->subdir[i]) // check if there are subdirectories to check
	{
		dir = opendir(checkdir); // open the directory
		while ((dirents = readdir(dir))) // everytime this is called we move to the next file in directory
		{
			if (!ft_strncmp(dirents->d_name, &globs->subdir[i][1], ft_strlen(dirents->d_name))) // if the file matches
			{
				j = 0;
				while (i >= j)
				{
					if (dirents->d_type == DT_DIR) // check if it is a directory
					{
						subdirs = ft_strjoin(subdirs, globs->subdir[j]); // add the current dir to subdirs
					}
					j++;
				}
				globs->matches = ft_vastrjoin(5, globs->matches, globs->pardir, dname, subdirs, " "); // adds the match? pretty sure it goes wrong here.
			}
		}
		closedir(dir);
		checkdir = ft_vastrjoin(2, checkdir, globs->subdir[i]); // create new checkdir for the next loop round
		i++;
	}
	dname[0] = type; // just here to stop warnings
}

int	ft_parsewildcard(t_globs *globs, char *dname, int i)
{
	int	j;

	j = 0;
	if (globs->gstart[0] == '.')
		globs->period = 1;
	if (i == 0 && globs->gend[i] == dname[j])// if first character of glob end matches
	{
		if (globs->period == 0)
			if (dname[0] == '.')
				return (1);
		if (globs->period == 1)
			if (dname[0] != '.')
				return (1);
	}
	while (dname[i])
	{
		if (dname[i] == globs->gend[j] || globs->gend[0] == '\0')
		{
			if (globs->gend[0] == '\0')
				return (1);
			while (dname[i + j] && globs->gend[j] && dname[i + j] == globs->gend[j])
				j++;
			if (dname[i + j] == '\0')
				return (1);
			else
				j = 0;
		}
		else
			i++;
	}
	return (0);
}

int	ft_matchtheglob(t_globs *globs, char *dname, int i)
{
	if (globs->glob == '*')
		if (ft_parsewildcard(globs, dname, i))
			return (1);
	/*if (globs->glob == '?')*/
		/*if (ft_parsejoker(globs, dname, i))*/
			/*return (1);*/
	/*if (globs->glob == '[')*/
		/*if (ft_parseanyof(globs, dname, i))*/
			/*return (1);*/
	return (0);
}

void	ft_matchtillglob(t_globs *globs, char *dname, char *fullpath, unsigned char type)
{ // match untill glob
	int i;

	i = 0;
	while (globs->gstart[i] == dname[i])
		i++;
	if (globs->gstart[i] == '\0') // Glob start matches
	{
		if (ft_matchtheglob(globs, dname, i)) // check if the rest of the glob also matches
		{
			if (globs->subdir[0]) //check if we need to match subdirs
			{
				if (type == DT_DIR) //check if it is an actual directory
					ft_matchsub(globs, dname, fullpath, type); // match the subdirectories recursively
			}
			else
				globs->matches = ft_vastrjoin(4, globs->matches, globs->pardir, dname, " "); // no subdir, so match is valid :)
		}
	}
}

int	ft_parseglob(t_cmds *cmd, t_globs *globs)
{
	DIR				*dir;
	struct dirent	*dirents;
	char			*curdir;
	char			*checkdir;

	curdir = ft_getpwd(cmd->envp, 1);
	checkdir = ft_vastrjoin(2, curdir, globs->pardir);
	dir = opendir(checkdir); // needs to run for every sub directory.
	if (dir)
	{	
		while ((dirents = readdir(dir))) // everytime this is called we move to the next file in directory
		{
			ft_matchtillglob(globs, dirents->d_name, checkdir, dirents->d_type);
		}
		closedir(dir);
	}
	if (globs->matches[0] == '\0')
	{
		globs->matches = ft_vastrjoin(5, globs->pardir, globs->gstart, "*", globs->gend, globs->subdir);
	}
	return (0);
}

void	ft_getsubdir(t_globs *globs)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	k = 0;
	while (globs->gend[k])
	{
		if (globs->gend[k] == '/')
		{
			globs->gend[k] = '\0';
			globs->subdir[i] = ft_calloc(ft_strlen(globs->gend), 8);
			globs->subdir[i][0] = '/';
			j = 1;
			while(globs->gend[k + j] && globs->gend[k + j] != '/')
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
	globs->subdir[i] = ft_calloc(ft_strlen(globs->gend), 8);
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
	int endpos;

	endpos = 0;
	globs->gstart[startpos] = '\0'; // set the \0 at the end
	startpos++;
	while (globs->pipeline[globs->linecount + startpos + endpos] && globs->pipeline[globs->linecount + startpos + endpos] != ' ')
	{ // while pipeline and pipeline is not ' '
		globs->gend[endpos] = globs->pipeline[globs->linecount + startpos + endpos]; // copy it over
		endpos++;
	}
	globs->gend[endpos] = '\0'; // set the \0 for the end glob
	globs->start = ft_substr(globs->pipeline, 0, globs->linecount); // copy globstart
	globs->end = ft_strdup(&globs->pipeline[globs->linecount + startpos + endpos]); // copy globend
	return (endpos);
}

void	ft_globlooper(t_globs *globs, t_cmds *cmd, int startpos)
{ // should parse all globs and not stop untill there are no more globs.
	while (globs->pipeline[globs->linecount + startpos]) // while there are characters on the pipeline
	{
		if (ft_strchr("\'\"", globs->pipeline[globs->linecount])) // if we find a quote
			startpos = ft_skipbutcopygstart(globs, startpos); // copy over the line untill the quote closes
		if (globs->pipeline[globs->linecount + startpos] == ' ') // if we find a space
		{
			globs->linecount = globs->linecount + startpos + 1; // we reset the startposition of the glob.
			startpos = 0;
		}
		if (ft_strchr("*?[", globs->pipeline[globs->linecount + startpos])) // if we find a glob
		{
			globs->glob = globs->pipeline[globs->linecount + startpos]; // set the glob type
			ft_getglob(globs, startpos); //extracts the glob, puts all characters before and after in 2 seperate strings
			ft_getparent(globs); //looks in the glob if it contains any extra directories above or below the glob
			ft_getsubdir(globs); //looks in the glob for any subdirs and puts them in their own char **
			ft_parseglob(cmd, globs); //parses the glob character by character
			ft_newpipeline(globs); //constructs the new pipeline, sets the new position in the pipeline right after the parsed glob
			if (cmd->debug)
				ft_printglobs(*globs, "globlooper");
			startpos++;
		}
		else // no glob found yet, copy over the character and restart the loop.
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
	globs->end = ft_calloc(linelenght, 8);
	globs->subdir = ft_calloc(linelenght, 128);
	globs->pardir = ft_calloc(linelenght, 8);
	globs->matches = ft_calloc(linelenght, 8);
	globs->pipeline = ft_strdup(pipeline);
	globs->linecount = 0;
	return (globs);
}

int	ft_parseglobs(t_cmds *cmd)
{ // this function initializes the globlooper that parses all the globs.
	t_globs			*globs;

	globs = ft_initglobstruct(cmd->pipeline); //init the struct
	// only one of the following will run, there is probably a more elegant solution for this.
	if (ft_checkoutquote(globs->pipeline, '*', 2) >= 0)
		ft_globlooper(globs, cmd, 0);
	if (ft_checkoutquote(globs->pipeline, '?', 2) >= 0)
		ft_globlooper(globs, cmd, 0);
	if (ft_checkoutquote(globs->pipeline, '[', 2) >= 0)
		ft_globlooper(globs, cmd, 0);
	cmd->pipeline = ft_strdup(globs->pipeline); // writes the glob pipeline to the cmd pipeline
	// free globs here
	return (0);
}
