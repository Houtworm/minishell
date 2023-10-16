/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   globtools.c                                     |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: houtworm <codam@houtworm.net>              //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/09/20 03:34:27 by houtworm     /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/10/16 10:51:17 by houtworm     \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_cleanpardir(t_globs *globs)
{
	int		oldcount;
	int		newcount;

	oldcount = 0;
	newcount = 0;
	while (globs->pardir[oldcount])
	{
		if (globs->pardir[oldcount] == '/')
		{
			oldcount++;
			newcount = oldcount;
			while (globs->pardir[oldcount] == '/')
				oldcount++;
			if (oldcount > newcount)
				while (globs->pardir[oldcount] && globs->pardir[oldcount] != '/')
				{
					globs->pardir[newcount] = globs->pardir[oldcount];
					oldcount++;
					newcount++;
				}
		}
		oldcount++;
	}
	globs->pardir[newcount] = '\0';
}

void	ft_cleansubdir(t_globs *globs)
{
	int		olddir;
	int		newdir;
	int		oldcount;
	int		newcount;

	olddir = 0;
	newdir = 0;
	while (globs->subdir[olddir])
	{
		while (globs->subdir[olddir] && globs->subdir[olddir][0] == '/' && globs->subdir[olddir][1] == '\0')
			olddir++;
		if (!globs->subdir[olddir])
		{
			newdir++;
			break;
		}
		oldcount = 0;
		newcount = 0;
		while (globs->subdir[olddir][oldcount])
		{
			if (globs->subdir[olddir][oldcount] == '/')
			{
				globs->subdir[newdir][newcount] = globs->subdir[olddir][oldcount];
				newcount++;
				oldcount++;
				while (globs->subdir[olddir][oldcount] == '/')
					oldcount++;
				while (globs->subdir[olddir][oldcount] && globs->subdir[olddir][oldcount] != '/')
				{
					globs->subdir[newdir][newcount] = globs->subdir[olddir][oldcount];
					newcount++;
					oldcount++;
				}
			}
			globs->subdir[newdir][newcount] = globs->subdir[olddir][oldcount];
			oldcount++;
			newcount++;
		}
		globs->subdir[newdir][newcount] = '\0';
		newdir++;
		olddir++;
	}
	while (newdir < olddir)
	{
		free(globs->subdir[newdir]);
		globs->subdir[newdir] = NULL;
		newdir++;
	}
}

void	ft_removequotesfromsubdir(t_globs *globs)
{
	int		i;
	int		j;
	int		k;
	char	quote;

	i = 0;
	while (globs->subdir[i])
	{
		j = 0;
		k = 0;
		while (globs->subdir[i][j])
		{
			if (ft_strchr("\'\"", globs->subdir[i][j]))
			{
				quote = globs->subdir[i][j];
				j++;
				while (globs->subdir[i][j] != quote)
				{
					if (ft_strchr("*?[", globs->subdir[i][j]))
					{
						globs->subdir[i][k] = '\\';
						k++;
					}
					globs->subdir[i][k] = globs->subdir[i][j];
					j++;
					k++;
				}
				j++;
			}
			if (globs->subdir[i][j])
			{
				globs->subdir[i][k] = globs->subdir[i][j];
				k++;
				j++;
			}
		}
		globs->subdir[i][k] = '\0';
		i++;
	}
}

void	ft_removequotesfrompardir(t_globs *globs)
{
	int		i;
	int		j;
	char	quote;

	i = 0;
	j = 0;
	while (globs->pardir[i])
	{
		if (ft_strchr("\'\"", globs->pardir[i]))
		{
			quote = globs->pardir[i];
			i++;
			while (globs->pardir[i] != quote)
			{
				globs->pardir[j] = globs->pardir[i];
				j++;
				i++;
			}
			i++;
		}
		while (globs->pardir[i] && !ft_strchr("\'\"", globs->pardir[i]))
		{
			globs->pardir[j] = globs->pardir[i];
			j++;
			i++;
		}
	}
	globs->pardir[j] = '\0';
}

void	ft_removequotesfromglobstart(t_globs *globs)
{
	int		i;
	int		j;
	char	quote;

	i = 0;
	j = 0;
	while (globs->gstart[i])
	{
		if (ft_strchr("\'\"", globs->gstart[i]))
		{
			quote = globs->gstart[i];
			i++;
			while (globs->gstart[i] != quote)
			{
				globs->gstart[j] = globs->gstart[i];
				j++;
				i++;
			}
			i++;
		}
		while (globs->gstart[i] && !ft_strchr("\'\"", globs->gstart[i]))
		{
			globs->gstart[j] = globs->gstart[i];
			j++;
			i++;
		}
	}
	globs->gstart[j] = '\0';
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

void	ft_cleanglob(t_globs *globs)
{
	ft_cleanpardir(globs);
	ft_cleansubdir(globs);
	ft_removequotesfrompardir(globs);
	ft_removequotesfromsubdir(globs);
	ft_removequotesfromglobstart(globs);
	ft_removequotesfromglobend(globs);
}

void	ft_backupglob(t_globs *globs)
{
	char	*temp;

	free(globs->backup);
	if (globs->subdir[0])
	{
		temp = ft_cpptostr(globs->subdir);
		globs->backup = ft_vastrjoin(5, globs->pardir, globs->gstart, globs->glob, globs->gend, temp);
		free(temp);
	}
	else
		globs->backup = ft_vastrjoin(4, globs->pardir, globs->gstart, globs->glob, globs->gend);
}

void	ft_addglobmatch(t_globs *globs, char *match)
{
	globs->matches[globs->matchcount] = ft_strdup(match);
	globs->matchcount++;
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
		ft_frearr(globs->matches);
		globs->matches = ft_calloc(100, 4096);
		free(globs->pipeline);
		globs->pipeline = ft_vastrjoin(3, globs->start, temp, globs->end);
		ft_frearr(globs->subdir);
		globs->subdir = ft_calloc(100, 128);
		globs->linecount = globs->linecount + k;
	}
	free(globs->anyof);
	globs->anyof = ft_calloc(100, 8);
	free(globs->backup);
	globs->backup = ft_calloc(10000, 8);
	free(globs->gend);
	globs->gend = ft_calloc(1000, 8);
	globs->matchcount = 0;
	free(temp);
	return (0);
}
