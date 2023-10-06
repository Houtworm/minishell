/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   tilde.c                                         |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: houtworm <codam@houtworm.net>              //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/10/06 16:38:04 by houtworm     /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/10/06 16:39:02 by houtworm     \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_parsetilde(t_cmds *cmds, t_shell shell)
{
	int		i;
	int		j;
	char	*begin;
	char	*temp;
	char	*rest;

	begin = ft_calloc((ft_strlen(cmds->pipeline) + 1), 8);
	rest = ft_calloc((ft_strlen(cmds->pipeline) + 1), 8);
	i = 0;
	while (cmds->pipeline[i])
	{
		j = 0;
		while (cmds->pipeline[i] && cmds->pipeline[i] != '~')
		{
			if (cmds->pipeline[i] == '\'')
			{
				begin[j] = cmds->pipeline[i];
				i++;
				j++;
				while (cmds->pipeline[i] && cmds->pipeline[i] != '\'')
				{
					begin[j] = cmds->pipeline[i];
					i++;
					j++;
				}
			}
			else if (cmds->pipeline[i] == '\"')
			{
				begin[j] = cmds->pipeline[i];
				i++;
				j++;
				while (cmds->pipeline[i] && cmds->pipeline[i] != '\"')
				{
					begin[j] = cmds->pipeline[i];
					i++;
					j++;
				}
			}
			begin[j] = cmds->pipeline[i];
			i++;
			j++;
		}
		if (cmds->pipeline[i] == '~')
		{
			begin[j] = '\0';
			i++;
			j = 0;
			while (cmds->pipeline[i])
			{
				rest[j] = cmds->pipeline[i];
				i++;
				j++;
			}
			rest[j] = '\0';
			free(cmds->pipeline);
			temp = ft_gethome(shell.envp);
			if (temp == NULL)
				cmds->pipeline = ft_strjoin(begin, rest);
			else
				cmds->pipeline = ft_vastrjoin(3, begin, temp, rest);
			i = 0;
			free(temp);
		}
	}
	ft_vafree(2, begin, rest);
}
