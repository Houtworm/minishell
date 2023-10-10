/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   globtools.c                                     |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: houtworm <codam@houtworm.net>              //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/09/20 03:34:27 by houtworm     /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/10/10 03:58:02 by houtworm     \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_cleanpardir(t_globs *globs)
{
	int		i;
	int		j;

	i = 0;
	while (globs->pardir[i])
	{
		if (globs->pardir[i] == '/')
		{
			i++;
			j = i;
			while (globs->pardir[i] == '/')
				i++;
			if (i > j)
				while (globs->pardir[i] && globs->pardir[i] != '/')
				{
					globs->pardir[j] = globs->pardir[i];
					i++;
					j++;
				}

		}
		i++;
	}
	globs->pardir[j] = '\0';
}

void	ft_cleansubdir(t_globs *globs)
{
	int		olddir;
	int		newdir;
	int		i;
	int		j;

	olddir = 0;
	newdir = 0;
	while (globs->subdir[olddir])
	{
		while (globs->subdir[olddir][0] == '/' && globs->subdir[olddir][1] == '\0')
			olddir++;
		if (!globs->subdir[olddir])
		{
			newdir++;
			break;
		}
		i = 0;
		j = 0;
		while (globs->subdir[olddir][i])
		{
			if (globs->subdir[olddir][i] == '/')
			{
				globs->subdir[newdir][j] = globs->subdir[olddir][i];
				i++;
				j++;
				while (globs->subdir[olddir][i] == '/')
					i++;
				while (globs->subdir[olddir][i] && globs->subdir[olddir][i] != '/')
				{
					globs->subdir[newdir][j] = globs->subdir[olddir][i];
					i++;
					j++;
				}
			}
			if (!globs->subdir[olddir][i])
				break;
			globs->subdir[newdir][j] = globs->subdir[olddir][i];
			i++;
			j++;
		}
		globs->subdir[newdir][j] = '\0';
		newdir++;
		olddir++;
	}
	while (newdir < olddir)
	{
		free(globs->subdir[newdir]);
		globs->subdir[newdir] = NULL;
		/*globs->subdir[newdir] = ft_calloc(10, 8);*/
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
					globs->subdir[i][k] = globs->subdir[i][j]; // copy it over
					j++;
					k++;
				}
				j++;
			}
			if (globs->subdir[i][j])
			{
				globs->subdir[i][k] = globs->subdir[i][j]; // copy it over
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
			/*printf("found first quote\n");*/
			quote = globs->pardir[i];
			i++;
			while (globs->pardir[i] != quote)
			{
				/*printf("copy over %c\n", globs->pardir[i]);*/
				globs->pardir[j] = globs->pardir[i]; // copy it over
				j++;
				i++;
			}
			i++;
		}
		while (globs->pardir[i] && !ft_strchr("\'\"", globs->pardir[i]))
		{
			/*printf("copy over %c\n", globs->pardir[i]);*/
			globs->pardir[j] = globs->pardir[i]; // copy it over
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
			/*printf("found first quote\n");*/
			quote = globs->gstart[i];
			i++;
			while (globs->gstart[i] != quote)
			{
				/*printf("copy over %c\n", globs->gstart[i]);*/
				globs->gstart[j] = globs->gstart[i]; // copy it over
				j++;
				i++;
			}
			i++;
		}
		while (globs->gstart[i] && !ft_strchr("\'\"", globs->gstart[i]))
		{
			/*printf("copy over %c\n", globs->gstart[i]);*/
			globs->gstart[j] = globs->gstart[i]; // copy it over
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
			/*printf("found first quote\n");*/
			quote = globs->gend[i];
			i++;
			while (globs->gend[i] != quote)
			{
				if (ft_strchr("*?[", globs->gend[i]))
				{
					globs->gend[j] = '\\';
					j++;
				}
				/*printf("copy over %c\n", globs->gend[i]);*/
				globs->gend[j] = globs->gend[i]; // copy it over
				j++;
				i++;
			}
			i++;
		}
		while (globs->gend[i] && !ft_strchr("\'\"", globs->gend[i]))
		{
			/*printf("copy over %c\n", globs->gend[i]);*/
			globs->gend[j] = globs->gend[i]; // copy it over
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

	if (globs->subdir[0])
	{
		temp = ft_cpptostr(globs->subdir);
		globs->backup = ft_vastrjoin(5, globs->pardir, globs->gstart, globs->glob, globs->gend, temp); // if there are no matches at all we need to restore the pipeline. subdirs are not correct here.
		free(temp);
	}
	else
		globs->backup = ft_vastrjoin(4, globs->pardir, globs->gstart, globs->glob, globs->gend); // if there are no matches at all we need to restore the pipeline. subdirs are not correct here.
}

void	ft_addglobmatch(t_globs *globs, char *match)
{
	globs->matches[globs->matchcount] = ft_strdup(match); // add the match
	/*printf("ft_addglobmatch added %s as a match\n", match);*/
	globs->matchcount++;
}

int	ft_newpipeline(t_globs *globs)
{ // simply parses the results into the new pipeline
	int		i;
	int		j;
	int		k;
	char	*temp;

	if (!globs->matches[0])
	{
		/*printf("ft_newpipeline no matches found\n");*/
		temp = ft_strdup(globs->backup); // if there are no matches at all we need to restore the pipeline. subdirs are not correct here.
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
		globs->pipeline = ft_vastrjoin(3, globs->start, temp, globs->end); // new pipeline
		ft_frearr(globs->subdir);
		globs->subdir = ft_calloc(100, 128);
		globs->linecount = globs->linecount + k; // new linecount
	}
	free(globs->anyof);
	globs->anyof = ft_calloc(100, 8);
	globs->matchcount = 0;
	free(temp);
	return (0);
}
