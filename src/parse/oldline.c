/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   oldline.c                                       |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: houtworm <codam@houtworm.net>              //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/10/06 16:38:21 by houtworm     /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/10/07 00:47:54 by djonker      \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*ft_parseoldline(t_shell *shell)
{
	int		i;
	int		j;
	char	*begin;
	char	*rest;

	i = 0;
	while (shell->line[i])
	{
		j = 0;
		begin = ft_calloc((ft_strlen(shell->line) + 1) * 8, 1);
		rest = ft_calloc((ft_strlen(shell->line) + 1) * 8, 1);
		while (shell->line[i] && (shell->line[i] != '!' || shell->line[i + 1] != '!'))
		{
			if (shell->line[i] == '\'')
			{
				begin[j] = shell->line[i];
				i++;
				j++;
				while (shell->line[i] && shell->line[i] != '\'')
				{
					begin[j] = shell->line[i];
					i++;
					j++;
				}
			}
			begin[j] = shell->line[i];
			i++;
			j++;
		}
		if (shell->line[i] == '!' && shell->line[i + 1] == '!')
		{
			if (!shell->oldline[0])
			{
				free(shell->oldline);
				shell->oldline = ft_strdup(shell->line);
				ft_vafree(2, begin, rest);
				return (shell->line);
			}
			begin[j] = '\0';
			i++;
			i++;
			j = 0;
			while (shell->line[i])
			{
				rest[j] = shell->line[i];
				i++;
				j++;
			}
			rest[j] = '\0';
			free(shell->line);
			shell->line = ft_vastrjoin(3, begin, shell->oldline, rest);
			i = 0;
		}
		free(rest);
		free(begin);
	}
	free(shell->oldline);
	shell->oldline = ft_strdup(shell->line);
	return (shell->line);
}
