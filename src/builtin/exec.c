/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   exec.c                                          |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: houtworm <codam@houtworm.net>              //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/10/01 00:57:08 by houtworm     /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/10/01 01:07:43 by houtworm     \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_exec(t_cmds cmds)
{
	int		i;
	char	**paths;
	
	i = 0;
	paths = ft_getpaths(cmds.envp, 1);
	while (cmds.arguments[i + 1])
	{
		free(cmds.arguments[i]);
		cmds.arguments[i] = ft_strdup(cmds.arguments[i + 1]);
		i++;
	}
	cmds.arguments[i] = NULL;
	cmds.absolute = ft_abspathcmd(paths, cmds.arguments[0]);
	execve(cmds.absolute, cmds.arguments, cmds.envp);
	exit(-1);
}
