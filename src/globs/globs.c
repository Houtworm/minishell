/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   globs.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: houtworm <codam@houtworm.net>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/03 09:12:54 by houtworm      #+#    #+#                 */
/*   Updated: 2023/10/20 18:51:53 by houtworm      ########   odam.nl         */
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

char	*ft_globcheckabsolute(t_globs *globs, char **envp)
{
	char	*curdir;
	char	*checkdir;

	if (globs->pardir[0] == '/')
		checkdir = ft_strdup(globs->pardir);
	else
	{
		curdir = ft_getpwd(envp, 1);
		checkdir = ft_vastrjoin(2, curdir, globs->pardir);
		free(curdir);
	}
	return (checkdir);
}

int	ft_parseglob(t_globs *globs, char **envp)
{
	DIR				*dir;
	struct dirent	*dirents;
	char			*checkdir;

	checkdir = ft_globcheckabsolute(globs, envp);
	dir = opendir(checkdir);
	if (dir)
	{
		dirents = readdir(dir);
		while (dirents)
		{
			ft_matchtillglob(globs, dirents->d_name, checkdir, dirents->d_type);
			dirents = readdir(dir);
		}
		closedir(dir);
	}
	free(checkdir);
	return (0);
}

int	ft_globfoundglob(t_globs *globs, t_commands *cmd, int startpos, char **envp)
{
	globs->glob[0] = globs->line[globs->linecount + startpos];
	ft_getglob(globs, startpos);
	ft_getparent(globs);
	ft_getsubdir(globs);
	ft_backupglob(globs);
	ft_removequotesfromglobstart(globs);
	ft_removequotesfromglobend(globs);
	ft_cleanpardir(globs);
	ft_cleansubdir(globs);
	ft_removequotesfrompardir(globs);
	ft_removequotesfromsubdir(globs);
	ft_parseglob(globs, envp);
	ft_newpipeline(globs);
	if (cmd->debug)
		ft_printglobs(*globs, "globlooper");
	return (0);
}

void	ft_globlooper(t_globs *globs, t_commands *cmd, int startpos, char **envp)
{
	while (globs->line[globs->linecount + startpos])
	{
		if (ft_strchr("\'\"", globs->line[globs->linecount + startpos]))
			startpos = ft_skipbutcopygstart(globs, startpos);
		else if (globs->line[globs->linecount + startpos] == ' ')
		{
			globs->linecount = globs->linecount + startpos + 1;
			ft_bzero(globs->gstart, startpos);
			startpos = 0;
		}
		else if (ft_strchr("*?[", globs->line[globs->linecount + startpos]))
			startpos = ft_globfoundglob(globs, cmd, startpos, envp);
		else if (globs->line[globs->linecount + startpos])
		{
			globs->gstart[startpos] = globs->line[globs->linecount + startpos];
			startpos++;
		}
	}
}

int	ft_parseglobs(t_commands *cmd, char **envp)
{
	t_globs			*globs;

	if (ft_checkoutquote(cmd->line, '*', 2) >= 0)
		globs = ft_initglobstruct(cmd->line);
	else if (ft_checkoutquote(cmd->line, '?', 2) >= 0)
		globs = ft_initglobstruct(cmd->line);
	else if (ft_checkoutquote(cmd->line, '[', 2) >= 0)
		globs = ft_initglobstruct(cmd->line);
	else
		return (0);
	ft_globlooper(globs, cmd, 0, envp);
	free(cmd->line);
	cmd->line = ft_strdup(globs->line);
	ft_freeglobs(globs);
	return (0);
}
