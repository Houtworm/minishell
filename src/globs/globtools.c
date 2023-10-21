/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   globtools.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: houtworm <codam@houtworm.net>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/20 03:34:27 by houtworm      #+#    #+#                 */
/*   Updated: 2023/10/21 13:34:54 by djonker       ########   odam.nl         */
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
