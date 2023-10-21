/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   globs.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: houtworm <codam@houtworm.net>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/03 09:12:54 by houtworm      #+#    #+#                 */
/*   Updated: 2023/10/21 15:52:02 by djonker       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*ft_globcheckabsolute(t_globs *globs, char **envp)
{
	char	*curdir;
	char	*checkdir;

	if (globs->pdir[0] == '/')
		checkdir = ft_strdup(globs->pdir);
	else
	{
		curdir = ft_getpwd(envp, 1);
		checkdir = ft_vastrjoin(2, curdir, globs->pdir);
		free(curdir);
	}
	return (checkdir);
}

int	ft_globstarter(t_globs *globs, char **envp)
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
	int	endpos;

	globs->glob[0] = globs->line[globs->li + startpos];
	globs->gsta[startpos] = '\0';
	startpos++;
	endpos = ft_getglob(globs, startpos, 0, 0);
	free(globs->start);
	globs->start = ft_substr(globs->line, 0, globs->li);
	free(globs->end);
	globs->end = ft_strdup(&globs->line[globs->li + startpos + endpos]);
	ft_getparent(globs, 0, 0);
	ft_getsubdir(globs, 0, 0, 0);
	ft_backupglob(globs);
	ft_removequotesfromglobstart(globs);
	ft_removequotesfromglobend(globs);
	ft_cleanpardir(globs, 0, 0);
	ft_cleansubdir(globs);
	ft_removequotesfrompardir(globs, 0, 0);
	ft_removequotesfromsubdir(globs);
	ft_globstarter(globs, envp);
	ft_newpipeline(globs);
	if (cmd->debug)
		ft_printglobs(*globs, "globlooper");
	return (0);
}

void	ft_globlooper(t_globs *globs, t_commands *cmd, int startp, char **envp)
{
	while (globs->line[globs->li + startp])
	{
		if (ft_strchr("\'\"", globs->line[globs->li + startp]))
			startp = ft_skipbutcopygstart(globs, startp);
		else if (globs->line[globs->li + startp] == ' ')
		{
			globs->li = globs->li + startp + 1;
			ft_bzero(globs->gsta, startp);
			startp = 0;
		}
		else if (ft_strchr("*?[", globs->line[globs->li + startp]))
			startp = ft_globfoundglob(globs, cmd, startp, envp);
		else if (globs->line[globs->li + startp])
		{
			globs->gsta[startp] = globs->line[globs->li + startp];
			startp++;
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
