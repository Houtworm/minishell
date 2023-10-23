/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   initglob.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: houtworm <codam@houtworm.net>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/20 03:32:43 by houtworm      #+#    #+#                 */
/*   Updated: 2023/10/23 23:21:30 by yitoh         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_skipbutcopygstart(t_globs *globs, int startpos)
{
	char	quote;

	if (ft_strchr("\'\"", globs->line[globs->li + startpos]))
	{
		quote = globs->line[globs->li + startpos];
		globs->gsta[startpos] = globs->line[globs->li + startpos];
		startpos++;
		while (globs->line[globs->li + startpos] != quote)
		{
			globs->gsta[startpos] = globs->line[globs->li + startpos];
			startpos++;
		}
		globs->gsta[startpos] = globs->line[globs->li + startpos];
		startpos++;
	}
	return (startpos);
}

void	ft_globmatches(t_globs *globs, char *dname, char type, char *fullpath)
{
	char	*temp;

	if (globs->sdir[0])
	{
		if ((unsigned char)type == DT_DIR)
		{
			temp = ft_vastrjoin(2, fullpath, dname);
			free(globs->tmpsdir[0]);
			globs->tmpsdir[0] = ft_strjoin("/", dname);
			ft_recursivematchsub(globs, temp, dname, 0);
			free(temp);
		}
	}
	else
	{
		temp = ft_vastrjoin(2, globs->pdir, dname);
		ft_addglobmatch(globs, temp);
		free(temp);
	}
}

void	ft_matchtillglob(t_globs *globs, char *dn, char *fullp, char type)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (globs->gsta[j + i] == '\\' || \
			(dn[i] && globs->gsta[j + i] == dn[i]))
	{
		if (globs->gsta[i + j] == '\\')
			j++;
		else
			i++;
	}
	if (globs->gsta[j + i] == '\0')
	{
		if (ft_firstglob(globs, dn, i))
		{
			ft_globmatches(globs, dn, type, fullp);
		}
	}
}

int	ft_getglob(t_globs *globs, int spos, int epos, char quote)
{
	while (globs->line[globs->li + spos + epos] && \
			globs->line[globs->li + spos + epos] != ' ')
	{
		if (ft_strchr("\'\"", globs->line[globs->li + spos + epos]))
		{
			quote = globs->line[globs->li + spos + epos];
			globs->gend[epos] = globs->line[globs->li + spos + epos];
			epos++;
			while (globs->line[globs->li + spos + epos] != quote)
			{
				globs->gend[epos] = globs->line[globs->li + spos + epos];
				epos++;
			}
			globs->gend[epos] = globs->line[globs->li + spos + epos];
			epos++;
		}
		else
		{
			globs->gend[epos] = globs->line[globs->li + spos + epos];
			epos++;
		}
	}
	globs->gend[epos] = '\0';
	return (epos);
}

t_globs	*ft_initglobstruct(char *line)
{
	t_globs			*globs;
	int				linelength;

	linelength = ft_strlen(line);
	globs = ft_calloc(linelength, 256);
	globs->gsta = ft_calloc(linelength, 8);
	globs->gend = ft_calloc(500, 8);
	globs->start = ft_calloc(linelength, 8);
	globs->end = ft_calloc(linelength, 8);
	globs->glob = ft_calloc(linelength, 8);
	globs->backup = ft_calloc(linelength, 8);
	globs->sdir = ft_calloc(linelength, 128);
	globs->tmpsdir = ft_calloc(linelength, 128);
	globs->pdir = ft_calloc(linelength * 2, 8);
	/*globs->dname = ft_calloc(linelength, 8);*/
	/*globs->fpath = ft_calloc(linelength, 800);*/
	globs->matches = ft_calloc(linelength, 4096);
	globs->line = ft_strdup(line);
	globs->li = 0;
	globs->matchcount = 0;
	return (globs);
}
