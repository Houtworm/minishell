/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   oldline.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: houtworm <codam@houtworm.net>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/06 16:38:21 by houtworm      #+#    #+#                 */
/*   Updated: 2023/10/20 12:36:42 by houtworm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*ft_oldlinebegin(int *i, t_shell *msh, char *begin)
{
	int		j;

	j = 0;
	while (msh->line[*i] && (msh->line[*i] != '!' || msh->line[*i + 1] != '!'))
	{
		if (msh->line[*i] == '\'')
		{
			begin[j] = msh->line[*i];
			(*i)++;
			j++;
			while (msh->line[*i] && msh->line[*i] != '\'')
			{
				begin[j] = msh->line[*i];
				(*i)++;
				j++;
			}
		}
		begin[j] = msh->line[*i];
		(*i)++;
		j++;
	}
	begin[j] = '\0';
	return (begin);
}

char	*ft_oldlinerest(t_shell *msh, int *i, char *begin, char *rest)
{
	int		j;

	j = 0;
	if (!msh->oldline[0])
	{
		ft_vafree(2, begin, rest);
		return (NULL);
	}
	(*i)++;
	(*i)++;
	j = 0;
	while (msh->line[*i])
	{
		rest[j] = msh->line[*i];
		(*i)++;
		j++;
	}
	rest[j] = '\0';
	return (rest);
}

char	*ft_parseoldline(t_shell *msh)
{
	int		i;
	char	*begin;
	char	*rest;

	i = 0;
	while (msh->line[i])
	{
		begin = ft_calloc((ft_strlen(msh->line) + 1) * 8, 1);
		rest = ft_calloc((ft_strlen(msh->line) + 1) * 8, 1);
		ft_oldlinebegin(&i, msh, begin);
		if (msh->line[i] == '!' && msh->line[i + 1] == '!')
		{
			if (!ft_oldlinerest(msh, &i, begin, rest))
				return (msh->line);
			free(msh->line);
			msh->line = ft_vastrjoin(3, begin, msh->oldline, rest);
			i = 0;
		}
		ft_vafree(2, rest, begin);
	}
	free(msh->oldline);
	msh->oldline = ft_strdup(msh->line);
	return (msh->line);
}
