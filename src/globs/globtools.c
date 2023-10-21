/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   globtools.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: houtworm <codam@houtworm.net>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/20 03:34:27 by houtworm      #+#    #+#                 */
/*   Updated: 2023/10/21 16:22:08 by djonker       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_globstartfoundquote(t_globs *globs, int *i, int *j)
{
	char	quote;

	quote = globs->gsta[*i];
	(*i)++;
	while (globs->gsta[*i] != quote)
	{
		globs->gsta[*j] = globs->gsta[*i];
		(*j)++;
		(*i)++;
	}
	(*i)++;
}

void	ft_removequotesfromglobstart(t_globs *globs)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (globs->gsta[i])
	{
		if (ft_strchr("\'\"", globs->gsta[i]))
			ft_globstartfoundquote(globs, &i, &j);
		while (globs->gsta[i] && !ft_strchr("\'\"", globs->gsta[i]))
		{
			globs->gsta[j] = globs->gsta[i];
			j++;
			i++;
		}
	}
	globs->gsta[j] = '\0';
}

void	ft_globendfoundquote(t_globs *globs, int *i, int *j)
{
	char	quote;

	quote = globs->gend[*i];
	(*i)++;
	while (globs->gend[*i] != quote)
	{
		if (ft_strchr("*?[", globs->gend[*i]))
		{
			globs->gend[*j] = '\\';
			(*j)++;
		}
		globs->gend[*j] = globs->gend[*i];
		(*j)++;
		(*i)++;
	}
	(*i)++;
}

void	ft_removequotesfromglobend(t_globs *globs)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (globs->gend[i])
	{
		if (ft_strchr("\'\"", globs->gend[i]))
			ft_globendfoundquote(globs, &i, &j);
		while (globs->gend[i] && !ft_strchr("\'\"", globs->gend[i]))
		{
			globs->gend[j] = globs->gend[i];
			j++;
			i++;
		}
	}
	globs->gend[j] = '\0';
}

void	ft_backupglob(t_globs *g)
{
	char	*temp;

	free(g->backup);
	if (g->sdir[0])
	{
		temp = ft_cpptostr(g->sdir);
		g->backup = ft_vastrjoin(5, g->pdir, g->gsta, g->glob, g->gend, temp);
		free(temp);
	}
	else
		g->backup = ft_vastrjoin(4, g->pdir, g->gsta, g->glob, g->gend);
}
