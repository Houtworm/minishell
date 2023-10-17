/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   tilde.c                                         |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: houtworm <codam@houtworm.net>              //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/10/06 16:38:04 by houtworm     /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/10/17 15:28:36 by houtworm     \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*ft_parsetilde(char *line, t_shell msh)
{
	int		i;
	int		j;
	char	*begin;
	char	*temp;
	char	*rest;

	begin = ft_calloc((ft_strlen(line) + 1), 8);
	rest = ft_calloc((ft_strlen(line) + 1), 8);
	i = 0;
	while (line[i])
	{
		j = 0;
		while (line[i] && line[i] != '~')
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
			else if (line[i] == '\"')
			{
				begin[j] = line[i];
				i++;
				j++;
				while (line[i] && line[i] != '\"')
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
		if (line[i] == '~')
		{
			begin[j] = '\0';
			i++;
			j = 0;
			while (line[i])
			{
				rest[j] = line[i];
				i++;
				j++;
			}
			rest[j] = '\0';
			free(line);
			temp = ft_gethome(msh.envp);
			if (temp == NULL)
				line = ft_strjoin(begin, rest);
			else
				line = ft_vastrjoin(3, begin, temp, rest);
			i = 0;
			free(temp);
		}
	}
	ft_vafree(2, begin, rest);
	return (line);
}
