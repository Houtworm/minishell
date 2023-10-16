/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   alias.c                                         |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: djonker <codam@houtworm.net>               //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/09/02 03:23:02 by djonker      /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/10/16 10:27:52 by houtworm     \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_parsealiases(t_commands *cmd, t_shell shell)
{
	int		i;
	char	*temp;
	int		varlen;

	i = 0;
	while (shell.alias[i].var)
	{
		varlen = ft_strlen(shell.alias[i].var);
		if (!ft_strncmp(shell.alias[i].var, cmd->pipeline, varlen))
		{
			if (cmd->pipeline[varlen] == ' ' || cmd->pipeline[varlen] == '\0')
			{
				temp = ft_strjoin(shell.alias[i].val, &cmd->pipeline[varlen]);
				free(cmd->pipeline);
				cmd->pipeline = ft_strdup(temp);
				free(temp);
			}
		}
		i++;
	}
}
