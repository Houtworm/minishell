/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   globs.c                                         |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: houtworm <codam@houtworm.net>              //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/09/03 09:12:54 by houtworm     /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/09/03 09:29:23 by houtworm     \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_parseglobs(t_cmds *cmd)
{
	char			*globstart;
	char			*globend;
	int				i;
	int				j;
	int				k;

	i = 0;
	j = 0;
	k = 0;
	globstart = ft_calloc(ft_strlen(cmd->pipeline), 8);
	globend = ft_calloc(ft_strlen(cmd->pipeline), 8);
	while (cmd->pipeline[i + j + k])
	{
		k = 0;
		if (cmd->pipeline[i + j] == '\'')
		{
			j++;
			while (cmd->pipeline[i + j] != '\'')
			{
				globstart[j] = cmd->pipeline[i + j];
				j++;
			}
			j++;
		}
		if (cmd->pipeline[i + j] == '\"')
		{
			j++;
			while (cmd->pipeline[i + j] != '\"')
			{
				globstart[j] = cmd->pipeline[i + j];
				j++;
			}
			j++;
		}
		if (cmd->pipeline[i + j] == ' ')
		{
			i = i + j + 1;
			j = 0;
		}
		if (cmd->pipeline[i + j] == '*')
		{
			globstart[j] = '\0';
			j++;
			while (cmd->pipeline[i + j + k] && !ft_strchr(" /", cmd->pipeline[i + j]))
			{
				globend[k] = cmd->pipeline[i + j + k];
				k++;
			}
			globend[k] = '\0';
			j++;
			cmd->pipeline = ft_vastrjoin(3, ft_substr(cmd->pipeline, 0, i), ft_parsewildcard(*cmd, globstart, globend), cmd->pipeline[i + j + k]);
		}
		globstart[j] = cmd->pipeline[i + j + k];
		j++;
	}
	return (0);
}
