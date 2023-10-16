/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   oldline.c                                       |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: houtworm <codam@houtworm.net>              //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/10/06 16:38:21 by houtworm     /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/10/16 11:46:21 by houtworm     \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*ft_parseoldline(t_shell *msh)
{
	int		i;
	int		j;
	char	*begin;
	char	*rest;

	i = 0;
	while (msh->line[i])
	{
		j = 0;
		begin = ft_calloc((ft_strlen(msh->line) + 1) * 8, 1);
		rest = ft_calloc((ft_strlen(msh->line) + 1) * 8, 1);
		while (msh->line[i] && (msh->line[i] != '!' || msh->line[i + 1] != '!'))
		{
			if (msh->line[i] == '\'')
			{
				begin[j] = msh->line[i];
				i++;
				j++;
				while (msh->line[i] && msh->line[i] != '\'')
				{
					begin[j] = msh->line[i];
					i++;
					j++;
				}
			}
			begin[j] = msh->line[i];
			i++;
			j++;
		}
		if (msh->line[i] == '!' && msh->line[i + 1] == '!')
		{
			if (!msh->oldline[0])
			{
				ft_vafree(2, begin, rest);
				return (msh->line);
			}
			begin[j] = '\0';
			i++;
			i++;
			j = 0;
			while (msh->line[i])
			{
				rest[j] = msh->line[i];
				i++;
				j++;
			}
			rest[j] = '\0';
			free(msh->line);
			msh->line = ft_vastrjoin(3, begin, msh->oldline, rest);
			i = 0;
		}
		free(rest);
		free(begin);
	}
	free(msh->oldline);
	msh->oldline = ft_strdup(msh->line);
	return (msh->line);
}
