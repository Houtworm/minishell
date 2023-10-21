/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   globtools.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: houtworm <codam@houtworm.net>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/20 03:34:27 by houtworm      #+#    #+#                 */
/*   Updated: 2023/10/21 13:13:56 by djonker       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_removequotesfromglobstart(t_globs *globs)
{
	int		i;
	int		j;
	char	quote;

	i = 0;
	j = 0;
	while (globs->gsta[i])
	{
		if (ft_strchr("\'\"", globs->gsta[i]))
		{
			quote = globs->gsta[i];
			i++;
			while (globs->gsta[i] != quote)
			{
				globs->gsta[j] = globs->gsta[i];
				j++;
				i++;
			}
			i++;
		}
		while (globs->gsta[i] && !ft_strchr("\'\"", globs->gsta[i]))
		{
			globs->gsta[j] = globs->gsta[i];
			j++;
			i++;
		}
	}
	globs->gsta[j] = '\0';
}

void	ft_removequotesfromglobend(t_globs *globs)
{
	int		i;
	int		j;
	char	quote;

	i = 0;
	j = 0;
	while (globs->gend[i])
	{
		if (ft_strchr("\'\"", globs->gend[i]))
		{
			quote = globs->gend[i];
			i++;
			while (globs->gend[i] != quote)
			{
				if (ft_strchr("*?[", globs->gend[i]))
				{
					globs->gend[j] = '\\';
					j++;
				}
				globs->gend[j] = globs->gend[i];
				j++;
				i++;
			}
			i++;
		}
		while (globs->gend[i] && !ft_strchr("\'\"", globs->gend[i]))
		{
			globs->gend[j] = globs->gend[i];
			j++;
			i++;
		}
	}
	globs->gend[j] = '\0';
}

void	ft_backupglob(t_globs *globs)
{
	char	*temp;

	free(globs->backup);
	if (globs->sdir[0])
	{
		temp = ft_cpptostr(globs->sdir);
		globs->backup = ft_vastrjoin(5, globs->pdir, globs->gsta, globs->glob, globs->gend, temp);
		free(temp);
	}
	else
		globs->backup = ft_vastrjoin(4, globs->pdir, globs->gsta, globs->glob, globs->gend);
}

void	ft_addglobmatch(t_globs *globs, char *match)
{
	globs->matches[globs->matchcount] = ft_strdup(match);
	globs->matchcount++;
}

void	ft_globcleannewline(t_globs *globs, char *temp, int k)
{
	if (globs->matches[0])
	{
		ft_frearr(globs->matches);
		globs->matches = ft_calloc(100, 4096);
		free(globs->line);
		globs->line = ft_vastrjoin(3, globs->start, temp, globs->end);
		ft_frearr(globs->sdir);
		globs->sdir = ft_calloc(100, 128);
		globs->linecount = globs->linecount + k;
	}
	ft_vafree(3, globs->anyof, globs->backup, globs->gend);
	globs->anyof = ft_calloc(100, 8);
	globs->backup = ft_calloc(10000, 8);
	globs->gend = ft_calloc(1000, 8);
	globs->matchcount = 0;
	free(temp);
}

int	ft_newpipeline(t_globs *globs)
{
	int		i;
	int		j;
	int		k;
	char	*temp;

	if (!globs->matches[0])
	{
		temp = ft_strdup(globs->backup);
		globs->linecount = globs->linecount + ft_strlen(temp);
	}
	else
	{
		temp = ft_calloc(100000, 8);
		k = 0;
		i = 0;
		while (globs->matches[i])
		{
			j = 0;
			if (ft_isallbyte(globs->matches[i], ' '))
			{
				temp[k] = '\'';
				k++;
			}
			while (globs->matches[i][j])
			{
				temp[k] = globs->matches[i][j];
				j++;
				k++;
			}
			if (ft_isallbyte(globs->matches[i], ' '))
			{
				temp[k] = '\'';
				k++;
			}
			temp[k] = ' ';
			k++;
			i++;
		}
		temp[k] = '\0';
	}
	ft_globcleannewline(globs, temp, k);
	return (0);
}
