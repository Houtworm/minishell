/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipe.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: houtworm <codam@houtworm.net>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/28 13:26:01 by houtworm      #+#    #+#                 */
/*   Updated: 2023/10/20 16:18:31 by houtworm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_getpipe(t_shell *msh, int i, int k)
{
	char	quote;
	int		count;

	count = 0;
	if (msh->line[i] == '\"' || msh->line[i] == '\'')
	{
		quote = msh->line[i];
		msh->frk[msh->forks].line[k] = msh->line[i];
		count++;
		while (msh->line[i + count] != quote)
		{
			msh->frk[msh->forks].line[k + count] = msh->line[i + count];
			count++;
		}
	}
	msh->frk[msh->forks].line[k + count] = msh->line[i + count];
	count++;
	if (msh->line[i + count] == '|' && msh->line[i + count + 1] == '|')
	{
		msh->frk[msh->forks].line[k + count] = msh->line[i + count];
		msh->frk[msh->forks].line[k + count + 1] = msh->line[i + count + 1];
		count += 2;
	}
	return (count);
}

t_shell	*ft_parsepipe(t_shell *msh)
{
	int		i;
	int		k;
	int		count;

	msh->frk = ft_calloc(2000, 16);
	i = 0;
	msh->forks = 0;
	while (msh->line[i])
	{
		k = 0;
		msh->frk[msh->forks].line = ft_calloc(ft_strlen(msh->line) * 8, 1);
		while (msh->line[i] && msh->line[i] != '|')
		{
			count = ft_getpipe(msh, i, k);
			k = k + count;
			i = i + count;
		}
		msh->frk[msh->forks].line[k] = '\0';
		if (msh->line[i])
			i++;
		msh->forks++;
	}
	return (msh);
}
