/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   oldline.c                                       |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: houtworm <codam@houtworm.net>              //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/10/06 16:38:21 by houtworm     /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/10/06 16:39:32 by houtworm     \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*ft_parseoldline(char *line, t_shell *shell)
{
	int		i;
	int		j;
	char	*begin;
	char	*rest;

	i = 0;
	while (line[i])
	{
		j = 0;
		begin = ft_calloc((ft_strlen(line) + 1) * 8, 1);
		rest = ft_calloc((ft_strlen(line) + 1) * 8, 1);
		while (line[i] && (line[i] != '!' || line[i + 1] != '!'))
		{
			if (line[i] == '\'')
			{
				begin[j] = line[i];
				i++;
				j++;
				while (line[i] && line[i] != '\'')
				{
					begin[j] = line[i];
					i++;
					j++;
				}
			}
			begin[j] = line[i];
			i++;
			j++;
		}
		if (line[i] == '!' && line[i + 1] == '!')
		{
			if (!shell->oldline[0])
			{
				ft_vafree(2, begin, rest);
				return (line);
			}
			begin[j] = '\0';
			i++;
			i++;
			j = 0;
			while (line[i])
			{
				rest[j] = line[i];
				i++;
				j++;
			}
			rest[j] = '\0';
			free (line);
			line = ft_vastrjoin(3, begin, shell->oldline, rest);
			i = 0;
		}
		free(rest);
		free(begin);
	}
	return (line);
}
