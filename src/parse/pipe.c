/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipe.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: houtworm <codam@houtworm.net>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/28 13:26:01 by houtworm      #+#    #+#                 */
/*   Updated: 2023/10/18 20:31:16 by yitoh         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_shell	*ft_parsepipe(t_shell *msh)
{
	int	i;
	int	k;

	msh->frk = ft_calloc(2000, 16);
	i = 0;
	msh->forkamount = 0;
	while (msh->line[i])
	{
		k = 0;
		msh->frk[msh->forkamount].line = ft_calloc(ft_strlen(msh->line) * 8, 1);
		while (!ft_strchr("|\"\'", msh->line[i]))
		{
			msh->frk[msh->forkamount].line[k] = msh->line[i];
			i++;
			k++;
			if (msh->line[i] == '|' && msh->line[i + 1] == '|')
			{
				msh->frk[msh->forkamount].line[k] = msh->line[i];
				msh->frk[msh->forkamount].line[k + 1] = msh->line[i + 1];
				i += 2;
				k += 2;
			}
		}
		if (msh->line[i] == '\"' || msh->line[i] == '\'')
		{
			i = ft_copyquote(&(msh->frk[msh->forkamount].line), msh->line, &k, i);
			if (msh->line[i] == '\"' || msh->line[i] == '\'')
				i = ft_copyquote(&(msh->frk[msh->forkamount].line), msh->line, &k, i);
			if (msh->line[i] == '|' && msh->line[i + 1] == '|')
			{
				msh->frk[msh->forkamount].line[k] = msh->line[i];
				msh->frk[msh->forkamount].line[k + 1] = msh->line[i + 1];
				i += 2;
				k += 2;
			}
			while (msh->line[i] && msh->line[i] != '|')
			{
				msh->frk[msh->forkamount].line[k] = msh->line[i];
				i++;
				k++;
				if (msh->line[i] == '|' && msh->line[i + 1] == '|')
				{
					msh->frk[msh->forkamount].line[k] = msh->line[i];
					msh->frk[msh->forkamount].line[k + 1] = msh->line[i + 1];
					i += 2;
					k += 2;
				}
			}
		}
		msh->frk[msh->forkamount].line[k] = '\0';
		if (msh->line[i] == '|'  && msh->line[i + 1] != '|')
		{
			i++;
			msh->forkamount++;
		}
	}
	msh->forkamount++;
	return (msh);
}
