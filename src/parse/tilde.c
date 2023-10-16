/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   tilde.c                                         |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: houtworm <codam@houtworm.net>              //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/10/06 16:38:04 by houtworm     /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/10/16 10:30:44 by houtworm     \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_parsetilde(t_commands *cmd, t_shell shell)
{
	int		i;
	int		j;
	char	*begin;
	char	*temp;
	char	*rest;

	begin = ft_calloc((ft_strlen(cmd->pipeline) + 1), 8);
	rest = ft_calloc((ft_strlen(cmd->pipeline) + 1), 8);
	i = 0;
	while (cmd->pipeline[i])
	{
		j = 0;
		while (cmd->pipeline[i] && cmd->pipeline[i] != '~')
		{
			if (cmd->pipeline[i] == '\'')
			{
				begin[j] = cmd->pipeline[i];
				i++;
				j++;
				while (cmd->pipeline[i] && cmd->pipeline[i] != '\'')
				{
					begin[j] = cmd->pipeline[i];
					i++;
					j++;
				}
			}
			else if (cmd->pipeline[i] == '\"')
			{
				begin[j] = cmd->pipeline[i];
				i++;
				j++;
				while (cmd->pipeline[i] && cmd->pipeline[i] != '\"')
				{
					begin[j] = cmd->pipeline[i];
					i++;
					j++;
				}
			}
			begin[j] = cmd->pipeline[i];
			i++;
			j++;
		}
		if (cmd->pipeline[i] == '~')
		{
			begin[j] = '\0';
			i++;
			j = 0;
			while (cmd->pipeline[i])
			{
				rest[j] = cmd->pipeline[i];
				i++;
				j++;
			}
			rest[j] = '\0';
			free(cmd->pipeline);
			temp = ft_gethome(shell.envp);
			if (temp == NULL)
				cmd->pipeline = ft_strjoin(begin, rest);
			else
				cmd->pipeline = ft_vastrjoin(3, begin, temp, rest);
			i = 0;
			free(temp);
		}
	}
	ft_vafree(2, begin, rest);
}
