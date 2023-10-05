/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   exec.c                                          |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: houtworm <codam@houtworm.net>              //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/10/01 00:57:08 by houtworm     /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/10/05 11:21:15 by houtworm     \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_exec(t_cmds cmds, t_shell *shell)
{
	int		i;
	int		status;
	char	**paths;
	
	i = 0;
	paths = ft_getpaths(shell->envp, 1);
	while (cmds.arguments[i + 1])
	{
		free(cmds.arguments[i]);
		cmds.arguments[i] = ft_strdup(cmds.arguments[i + 1]);
		i++;
	}
	cmds.arguments[i] = NULL;
	free(cmds.absolute);
	cmds.absolute = ft_abspathcmd(paths, cmds.arguments[0]);
	ft_frearr(paths);
	status = ft_checkcommand(cmds, shell->envp);
	if (status)
		status = 127;
	else
		execve(cmds.absolute, cmds.arguments, shell->envp);
	free(cmds.absolute);
	return (status);
	shell = shell;
}
