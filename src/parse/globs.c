/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   globs.c                                         |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: houtworm <codam@houtworm.net>              //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/09/03 09:12:54 by houtworm     /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/09/15 16:55:57 by djonker      \___)=(___/                 */
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

int		ft_recursivesubwildcard(t_globs *globs, struct dirent *dirents, int i, int j)
{
	printf("ft_recursivesubwildcard starting in recursivesubwildcard\n");
	if ((globs->subdir[i][0] == '.' && dirents->d_name[0] == '.') || (globs->subdir[i][0] != '.' && dirents->d_name[0] != '.')) // if first character of globstart is not a .
	{
		printf("ft_recursivesubwildcard periods match\n");
		if (globs->subdir[i][j] == '\0' || dirents->d_name[j] == '\0') // the whole filename matches
		{
			printf("ft_recursivesubwildcard just a * so %s matches too\n", dirents->d_name);
			globs->tempsubdir[i] = ft_strjoin("/", dirents->d_name);
			return (1); // copy it over.
		}
		while (dirents->d_name[j]) // while there are characters in filename 
		{
			printf("ft_recursivesubwildcard going into dirents dname loop, %d, %d, %c, %c\n", i, j, globs->subdir[i][j + 1], dirents->d_name[j]);
			while (dirents->d_name[j] && globs->subdir[i][j + 1] && dirents->d_name[j] == globs->subdir[i][j + 1]) //while the first character was a match but globend exists
			{
				printf("ft_recursivesubwildcard fast match in recsubwc: %d, %c, %c\n", j, globs->subdir[i][j + 1], dirents->d_name[j]);
				j++;
			}
			if (globs->subdir[i][j + 1] == '\0') // no globend means every end matches
			{
				if (dirents->d_type == DT_DIR) // check if it is a directory
				{
					printf("ft_recursivesubwildcard glob matches %s will be replaced with /%s in subdir %d\n", globs->subdir[i], dirents->d_name, i);
					globs->tempsubdir[i] = ft_strjoin("/", dirents->d_name);
					return (1); // this one is a match
				}
				else
				{
					if (globs->subdir[i + 1])
					{
						printf("ft_recursivesubwildcard %s matches but is not a dir and not the final subdir so no match\n", dirents->d_name);
						return (0);
					}
					else
					{
						globs->tempsubdir[i] = ft_strjoin("/", dirents->d_name);
						printf("ft_recursivesubwildcard %s matches but is not a dir but it is the final subdir so it will be added as a match\n", dirents->d_name);
						return (1);
					}
				}
			}
			if (ft_strchr("*?[", globs->subdir[i][j + 1])) // if we find a new glob
			{
				printf("ft_recursivesubwildcard recursivesubwildcard recursion\n");
				globs->tempsubdir[i] = ft_strjoin("/", dirents->d_name);
				return (ft_recursivesubdir(globs, dirents, i, j)); // recursive glob function returns 1 if it eventually matches
			}
			j++;
		}
	}
	printf("ft_recursivesubwildcard return 0?\n");
	return (0);
}

int		ft_recursivesubdir(t_globs *globs, struct dirent *dirents, int i, int j)
{
	if (globs->subdir[i][j] == '*')
	{
		printf("ft_recursivesubdir found * glob going into recursivesubwildcard\n");
		return (ft_recursivesubwildcard(globs, dirents, i, j + 1));
	}
	/*if (globs->subdir[i][j + 1] == '?')*/
	/*{*/
		/*ft_recursivesubjoker(globs, dname, i, j);*/
	/*}*/
	/*if (globs->subdir[i][j + 1] == '[')*/
	/*{*/
		/*ft_recursivesubanyof(globs, dname, i, j);*/
	/*}*/
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

	printf("ft_matchsub Start matching subdirs for %s\n", dname);
	i = 0;
	checkdir = ft_vastrjoin(2, fullpath, dname); // create the new directory to open
	while (globs->subdir[i]) // check if there are subdirectories to check
	{
		dir = opendir(checkdir); // open the directory
		if (!dir)
			return ;
		while ((dirents = readdir(dir))) // everytime this is called we move to the next file in directory
		{
			subdirs = NULL;
			printf("ft_matchsub trying to match %s in %s\n", dirents->d_name, dname);
			if ((globs->subdir[i][0] == '.' && dirents->d_name[0] == '.') || (globs->subdir[i][0] != '.' && dirents->d_name[0] != '.')) // if first character of globstart is not a .
			{
				j = 0;
				while (dirents->d_name[j] && dirents->d_name[j] == globs->subdir[i][j + 1]) //just skip over the non globs
				{
					printf("ft_matchsub fast match before glob: %d, %c, %c\n", j, globs->subdir[i][j + 1], dirents->d_name[j]);
					j++;
				}
				/*printf("ft_matchsub fast match broken: %d, %c, %c\n", j, globs->subdir[i][j + 1], dirents->d_name[j]);*/
				if (ft_strchr("*?[", globs->subdir[i][j + 1])) // we match the current character with a glob
				{
					printf("ft_matchsub glob found in %s in %s\n", dirents->d_name, dname);
					if (ft_recursivesubdir(globs, dirents, i, j + 1)) // returns a 1 if the glob matches
					{
						printf("ft_matchsub subdirs after recursive glob match: %s\n", subdirs);
						subdirs = ft_strjoin(subdirs, globs->tempsubdir[i]); // add the current dir to subdirs
						if (!globs->subdir[i + 1]) // if it is the last subdir
						{
							printf("ft_matchsub no subdirectory remaining,adding to matches\n");
							globs->matches = ft_vastrjoin(5, globs->matches, globs->pardir, dname, subdirs, " "); // add the match
						}
						/*else*/
						/*{*/
							/*printf("ft_matchsub need to do next subdirectory\n");*/
							/*globs->tempsubdir[i] = ft_strjoin("/", dirents->d_name);*/
						/*}*/
					}	
				}
				if (globs->subdir[i][j + 1] == '\0') // glob matches completely
				{
					printf("ft_matchsub glob matches completely\n");
					if (dirents->d_type == DT_DIR) // check if it is a directory
					{
						globs->tempsubdir[i] = ft_strjoin("/", dirents->d_name);
						subdirs = ft_strjoin(subdirs, globs->tempsubdir[i]); // add the current dir to subdirs
						printf("ft_matchsub subdirs after non recursive glob match: %s\n", subdirs);
					}
					if (!globs->subdir[i + 1]) // if it is the last subdir
					{
						printf("ft_matchsub found final subdir: %s%s%s\n", globs->pardir, dname, subdirs);
						globs->matches = ft_vastrjoin(5, globs->matches, globs->pardir, dname, subdirs, " "); // add the match
					}
				}
			}
		}
		closedir(dir);
		checkdir = ft_vastrjoin(2, checkdir, globs->tempsubdir[i]); // create new checkdir for the next loop round
		printf("ft_matchsub checkdir new loop %s\n", checkdir);
		i++;
	}
	printf("ft_matchsub finished matching subdirs for %s\n", dname);
	dname[0] = type; // just here to stop warnings
}

int	ft_recursivewildcard(t_globs *globs, char *dname, int i, int j)
{
	int		tempj;

	j++;
	tempj = j;
	if (globs->gend[j] == '\0') // no globend means every end matches
		return (1); // this one is a match
	while (dname[i + j]) // while there are characters in filename 
	{
		if (dname[i + j] == globs->gend[j] || globs->gend[j] == '\0') // if the first character matches or there is no globend
		{
			if (globs->gend[j] == '\0') // no globend means every end matches
				return (1); // this one is a match
			if (dname[i + j + 1] == '\0') // no globend means every end matches
				return (1); // this one is a match
			while (dname[i + j] && globs->gend[j] && dname[i + j] == globs->gend[j]) //while the first character was a match but globend exists
				j++;
			if (ft_strchr("*/[", globs->gend[j])) // if we find a new glob
				return (ft_recursiveglob(globs, dname, i, j)); // recursive glob function returns 1 if it eventually matches
			if (dname[i + j] == '\0') // the whole filename matches
				return (1); // copy it over.
			else // we have no match and reset the globend counter.
			{
				j = tempj;
			}
		}
		i++;
	}
	return (0);
}

int	ft_recursiveglob(t_globs *globs, char *dname, int i, int j)
{
	if (globs->gend[j] == '*')
	{
		return (ft_recursivewildcard(globs, dname, i, j));
	}
	/*if (globs->gend[j] == '?')*/
	/*{*/
		/*ft_recursivejoker(globs, dname, i, j);*/
	/*}*/
	/*if (globs->gend[j] == '[')*/
	/*{*/
		/*ft_recursiveanyof(globs, dname, i, j);*/
	/*}*/
	return (0);
}

int	ft_parsewildcard(t_globs *globs, char *dname, int i)
{
	int	j;

	j = 0;
	if (globs->gstart[0] != '.' && dname[0] == '.') // if there is a period mismatch
	{
		ft_printf("ft_parsewildcard Periods don't match\n");
		return (0); // we don't want to parse this one.
	}
	while (dname[i]) // while there are characters in filename 
	{
		if (dname[i] == globs->gend[j] || globs->gend[0] == '\0') // if the first character matches or there is no globend
		{
			if (globs->gend[0] == '\0') // no globend means every end matches
			{
				printf("ft_parsewildcard no characters after glob so this matches\n");
				return (1); // this one is a match
			}
			while (dname[i + j] && globs->gend[j] && dname[i + j] == globs->gend[j]) //while the first character was a match but globend exists
			{
				printf("ft_parsewildcard fastmatch %c\n", dname[i + j]);
				j++;
			}
			if (dname[i + j] == '\0') // the whole filename matches
			{
				printf("ft_parsewildcard whole filename matches\n");
				return (1); // copy it over.
			}
			if (ft_strchr("*?[", globs->gend[j])) // if we find a new glob
			{
				printf("ft_parsewildcard recursive glob found\n");
				return (ft_recursiveglob(globs, dname, i, j)); // recursive glob function returns 1 if it eventually matches
			}
			else // we have no match and reset the globend counter.
				j = 0;
		}
		else // no matching first character means we can move over a character and try to match from there.
			i++;
	}
	return (0); // no matches found.
}

int	ft_matchtheglob(t_globs *globs, char *dname, int i)
{ // maybe put a while loop here to handle multiple globs in the same path dir
	if (globs->glob == '*') // if we find a wildcard match
		if (ft_parsewildcard(globs, dname, i)) // parse it
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
	while (globs->gstart[i] == dname[i]) // while characters match
		i++;
	if (globs->gstart[i] == '\0') // Glob start matches
	{
		printf("ft_matchtillglob globs start matches with %s\n", dname);
		if (ft_matchtheglob(globs, dname, i)) // check if the rest of the glob also matches
		{
			printf("ft_matchtillglob glob matches with %s\n", dname);
			if (globs->subdir[0]) //check if we need to match subdirs
			{
				printf("ft_matchtillglob Match found, checking if dir\n");
				if (type == DT_DIR) //check if it is an actual directory
				{
					printf("ft_matchtillglob %s is a dir, going to match the subdirectory\n", dname);
					ft_matchsub(globs, dname, fullpath, type); // match the subdirectories recursively
				}
			}
			else
			{
				printf("ft_matchtillglob no subdirectory found, %s matches\n", dname);
				globs->matches = ft_vastrjoin(4, globs->matches, globs->pardir, dname, " "); // no subdir, so match is valid :)
			}
		}
	}
}

int	ft_parseglob(t_cmds *cmd, t_globs *globs)
{
	DIR				*dir;
	struct dirent	*dirents;
	char			*curdir;
	char			*checkdir;

	curdir = ft_getpwd(cmd->envp, 1); // get working directory
	checkdir = ft_vastrjoin(2, curdir, globs->pardir); // strjoin current directory and any directories before the first glob.
	dir = opendir(checkdir); // needs to run for every sub directory.
	if (dir)
	{	
		while ((dirents = readdir(dir))) // everytime this is called we move to the next file in directory
		{
			printf("ft_parseglob trying to match %s\n", dirents->d_name);
			ft_matchtillglob(globs, dirents->d_name, checkdir, dirents->d_type); // if it matches till the glob it will branch out from this function.
		}
		closedir(dir);
	}
	if (globs->matches[0] == '\0')
	{
		printf("ft_parseglob parseglob no matches found\n");
		globs->matches = ft_vastrjoin(5, globs->pardir, globs->gstart, "*", globs->gend, globs->subdir[0]); // if there are no matches at all we need to restore the pipeline. subdirs are not correct here.
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
	while (globs->gend[k]) // looping trough the globend for subdirectories
	{
		if (globs->gend[k] == '/') // if we find a / it means we found a subdir
		{
			globs->gend[k] = '\0'; // here we set the endpoint for the globend as subdirectories shouldn't be there
			globs->subdir[i] = ft_calloc(ft_strlen(globs->gend), 8); // malloc
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
	/*globs->subdir[i] = ft_calloc(ft_strlen(globs->gend), 8); // NULL terminated char***/
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
			startpos = 0;
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
	globs->tempsubdir = ft_calloc(linelenght, 128);
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
