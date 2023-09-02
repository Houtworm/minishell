/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   alias.c                                         |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: djonker <codam@houtworm.net>               //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/09/02 03:23:02 by djonker      /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/09/02 04:54:09 by djonker      \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_parsealiases(t_cmds *cmds, t_shell shell)
{
	int		i;
	char	*temp;
	int		varlen;

	i = 0;
	while (shell.alias[i].var)
	{
		varlen = ft_strlen(shell.alias[i].var);
		if (!ft_strncmp(shell.alias[i].var, cmds->pipeline, varlen))
		{
			if (cmds->pipeline[varlen] == ' ' || cmds->pipeline[varlen] == '\0')
			{
				temp = ft_strjoin(shell.alias[i].val, &cmds->pipeline[varlen]);
				free(cmds->pipeline);
				cmds->pipeline = ft_strdup(temp);
				free(temp);
			}
		}
		i++;
	}
}
