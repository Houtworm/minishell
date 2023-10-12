/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   globs.c                                         |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: houtworm <codam@houtworm.net>              //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/09/03 09:12:54 by houtworm     /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/10/12 13:09:55 by houtworm     \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_skipbutcopygstart(t_globs *globs, int startpos)
{ // copies over characters between quotes so the globs don't get parsed
	char	quote;
	
	if (ft_strchr("\'\"", globs->pipeline[globs->linecount + startpos])) // if current position is '
	{
		quote = globs->pipeline[globs->linecount + startpos];
		globs->gstart[startpos] = globs->pipeline[globs->linecount + startpos]; // copy copy copy
		startpos++;
		while (globs->pipeline[globs->linecount + startpos] != quote)
		{ // while current positon is not '
			globs->gstart[startpos] = globs->pipeline[globs->linecount + startpos]; // copy copy copy
			startpos++;
		}
		globs->gstart[startpos] = globs->pipeline[globs->linecount + startpos]; // copy copy copy
		startpos++;
	}
	/*globs->linecount = globs->linecount + startpos; // move the line counter accordingly*/
	return (startpos);
}

void	ft_matchtillglob(t_globs *globs, char *dname, char *fullpath, unsigned char type)
{ // match untill glob
	int 	i;
	int 	j;
	char	*temp;

	i = 0;
	j = 0;
	while (globs->gstart[j + i] == '\\' || (dname[i] && globs->gstart[j + i] == dname[i])) // while characters match
	{
		if (globs->gstart[i + j] == '\\')
		{
			/*printf("ft_matchtillglob found \\ skipping one character in gend\n");*/
			j++;
		}
		else
		{
			/*printf("ft_matchtillglob fast match before glob: %c, %c\n", globs->gstart[j + i], dname[i]);*/
			i++;
		}
	}
	if (globs->gstart[j + i] == '\0') // Glob start matches
	{
		/*printf("ft_matchtillglob globs start matches with %s\n", dname);*/
		if (ft_firstglob(globs, dname, i)) // check if the rest of the glob also matches
		{
			/*printf("ft_matchtillglob glob matches with %s\n", dname);*/
			if (globs->subdir[0]) //check if we need to match subdirs
			{
				/*printf("ft_matchtillglob Match found, checking if dir\n");*/
				if (type == DT_DIR) //check if it is an actual directory
				{
					/*printf("ft_matchtillglob %s is a dir, going to match the subdirectory\n", dname);*/
					temp = ft_vastrjoin(2, fullpath, dname);
					free(globs->tempsubdir[0]);
					globs->tempsubdir[0] = ft_strjoin("/", dname);
					ft_recursivematchsub(globs, temp, dname, 0); // match the subdirectories recursively
					free(temp);
				}
			}
			else
			{
				temp = ft_vastrjoin(2, globs->pardir, dname);
				ft_addglobmatch(globs, temp); // add the match
				free(temp);
			}
		}
	}
}

int	ft_parseglob(t_globs *globs, char **envp)
{
	DIR				*dir;
	struct dirent	*dirents;
	char			*curdir;
	char			*checkdir;

	if (globs->pardir[0] == '/')
		checkdir = ft_strdup(globs->pardir); // needs to run for every sub directory.
	else
	{
		curdir = ft_getpwd(envp, 1); // get working directory
		checkdir = ft_vastrjoin(2, curdir, globs->pardir); // strjoin current directory and any directories before the first glob.
		free(curdir);
	}
	dir = opendir(checkdir); // needs to run for every sub directory.
	if (dir)
	{	
		while ((dirents = readdir(dir))) // everytime this is called we move to the next file in directory
		{
			/*printf("ft_parseglob trying to match %s\n", dirents->d_name);*/
			ft_matchtillglob(globs, dirents->d_name, checkdir, dirents->d_type); // if it matches till the glob it will branch out from this function.
		}
		closedir(dir);
	}
	free(checkdir);
	return (0);
}

void	ft_globlooper(t_globs *globs, t_cmds *cmd, int startpos, char **envp)
{ // should parse all globs and not stop untill there are no more globs.
	while (globs->pipeline[globs->linecount + startpos]) // while there are characters on the pipeline
	{
		if (ft_strchr("\'\"", globs->pipeline[globs->linecount + startpos])) // if we find a quote
		{

			/*printf("going into quote: %s, %d\n", globs->gstart, startpos);*/
			startpos = ft_skipbutcopygstart(globs, startpos); // copy over the line untill the quote closes
		}
		else if (globs->pipeline[globs->linecount + startpos] == ' ') // if we find a space
		{
			/*printf("going into space: %s, %d\n", globs->gstart, startpos);*/
			globs->linecount = globs->linecount + startpos + 1; // we reset the startposition of the glob.
			ft_bzero(globs->gstart, startpos);
			startpos = 0;
		}
		else if (ft_strchr("*?[", globs->pipeline[globs->linecount + startpos])) // if we find a glob
		{
			/*printf("going into glob: %s, %d\n", globs->gstart, startpos);*/
			globs->glob[0] = globs->pipeline[globs->linecount + startpos]; // set the glob type
			ft_getglob(globs, startpos); //extracts the glob, puts all characters before and after in 2 seperate strings
			ft_getparent(globs); //looks in the glob if it contains any extra directories above the glob
			ft_getsubdir(globs); //looks in the glob for any subdirs and puts them in their own char **
			ft_backupglob(globs); // stores the old glob with any quotes and double slashes
			ft_cleanglob(globs); // removes stuff that is irrelevant
			ft_parseglob(globs, envp); //parses the glob character by character
			ft_newpipeline(globs); //constructs the new pipeline, sets the new position in the pipeline right after the parsed glob
			if (cmd->debug)
				ft_printglobs(*globs, "globlooper");
			startpos = 0;
		}
		else if (globs->pipeline[globs->linecount + startpos]) // no glob found yet, copy over the character and restart the loop.
		{
			/*printf("going into else: %s, %d\n", globs->gstart, startpos);*/
			globs->gstart[startpos] = globs->pipeline[globs->linecount + startpos];
			startpos++;
		}
		/*printf("gstart in globlooper: %s, %d\n", globs->gstart, startpos);*/
	}
}

int	ft_parseglobs(t_cmds *cmd, char **envp)
{
	t_globs			*globs;

	if (ft_checkoutquote(cmd->pipeline, '*', 2) >= 0)
		globs = ft_initglobstruct(cmd->pipeline);
	else if (ft_checkoutquote(cmd->pipeline, '?', 2) >= 0)
		globs = ft_initglobstruct(cmd->pipeline);
	else if (ft_checkoutquote(cmd->pipeline, '[', 2) >= 0)
		globs = ft_initglobstruct(cmd->pipeline);
	else
		return (0);
	ft_globlooper(globs, cmd, 0, envp);
	free(cmd->pipeline);
	cmd->pipeline = ft_strdup(globs->pipeline);
	ft_freeglobs(globs);
	return (0);
}
