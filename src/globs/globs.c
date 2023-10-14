/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   globs.c                                         |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: houtworm <codam@houtworm.net>              //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/09/03 09:12:54 by houtworm     /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/10/14 06:11:12 by djonker      \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_skipbutcopygstart(t_globs *globs, int startpos)
{
	char	quote;
	
	if (ft_strchr("\'\"", globs->pipeline[globs->linecount + startpos]))
	{
		quote = globs->pipeline[globs->linecount + startpos];
		globs->gstart[startpos] = globs->pipeline[globs->linecount + startpos];
		startpos++;
		while (globs->pipeline[globs->linecount + startpos] != quote)
		{
			globs->gstart[startpos] = globs->pipeline[globs->linecount + startpos];
			startpos++;
		}
		globs->gstart[startpos] = globs->pipeline[globs->linecount + startpos];
		startpos++;
	}
	return (startpos);
}

void	ft_matchtillglob(t_globs *globs, char *dname, char *fullpath, unsigned char type)
{
	int 	i;
	int 	j;
	char	*temp;

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
	}
}

int	ft_parseglob(t_globs *globs, char **envp)
{
	DIR				*dir;
	struct dirent	*dirents;
	char			*curdir;
	char			*checkdir;

	if (globs->pardir[0] == '/')
		checkdir = ft_strdup(globs->pardir);
	else
	{
		curdir = ft_getpwd(envp, 1);
		checkdir = ft_vastrjoin(2, curdir, globs->pardir);
		free(curdir);
	}
	dir = opendir(checkdir);
	if (dir)
	{	
		while ((dirents = readdir(dir)))
		{
			ft_matchtillglob(globs, dirents->d_name, checkdir, dirents->d_type);
		}
		closedir(dir);
	}
	free(checkdir);
	return (0);
}

void	ft_globlooper(t_globs *globs, t_cmds *cmd, int startpos, char **envp)
{
	while (globs->pipeline[globs->linecount + startpos])
	{
		if (ft_strchr("\'\"", globs->pipeline[globs->linecount + startpos]))
			startpos = ft_skipbutcopygstart(globs, startpos);
		else if (globs->pipeline[globs->linecount + startpos] == ' ')
		{
			globs->linecount = globs->linecount + startpos + 1;
			ft_bzero(globs->gstart, startpos);
			startpos = 0;
		}
		else if (ft_strchr("*?[", globs->pipeline[globs->linecount + startpos]))
		{
			globs->glob[0] = globs->pipeline[globs->linecount + startpos];
			ft_getglob(globs, startpos);
			ft_getparent(globs);
			ft_getsubdir(globs);
			ft_backupglob(globs);
			ft_cleanglob(globs);
			ft_parseglob(globs, envp);
			ft_newpipeline(globs);
			if (cmd->debug)
				ft_printglobs(*globs, "globlooper");
			startpos = 0;
		}
		else if (globs->pipeline[globs->linecount + startpos])
		{
			globs->gstart[startpos] = globs->pipeline[globs->linecount + startpos];
			startpos++;
		}
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
