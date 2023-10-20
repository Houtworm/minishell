/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tilde.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: houtworm <codam@houtworm.net>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/06 16:38:04 by houtworm      #+#    #+#                 */
/*   Updated: 2023/10/20 13:23:54 by houtworm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*ft_tildebegin(char *line, int *i, char *begin)
{
	int		j;
	char	quote;

	j = 0;
	while (line[*i] && line[*i] != '~')
	{
		if (line[*i] == '\'' || line[*i] == '\"')
		{
			quote = line[*i];
			begin[j] = line[*i];
			(*i)++;
			j++;
			while (line[*i] && line[*i] != quote)
			{
				begin[j] = line[*i];
				(*i)++;
				j++;
			}
		}
		begin[j] = line[*i];
		(*i)++;
		j++;
	}
	begin[j] = '\0';
	return (begin);
}

char	*ft_tildenewline(char *line, char *begin, int *i, t_shell msh)
{
	int		j;
	char	*rest;
	char	*temp;

	j = 0;
	rest = ft_calloc((ft_strlen(line) + 1), 8);
	while (line[*i])
	{
		rest[j] = line[*i];
		(*i)++;
		j++;
	}
	rest[j] = '\0';
	free(line);
	temp = ft_gethome(msh.envp);
	if (temp == NULL)
		line = ft_strjoin(begin, rest);
	else
		line = ft_vastrjoin(3, begin, temp, rest);
	free(temp);
	free(rest);
	return (line);
}

char	*ft_parsetilde(char *line, t_shell msh)
{
	int		i;
	char	*begin;

	begin = ft_calloc((ft_strlen(line) + 1), 8);
	i = 0;
	while (line[i])
	{
		begin = ft_tildebegin(line, &i, begin);
		if (line[i] == '~')
		{
			i++;
			line = ft_tildenewline(line, begin, &i, msh);
			i = 0;
		}
	}
	free(begin);
	return (line);
}
