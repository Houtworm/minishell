/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   exec.c                                          |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: houtworm <codam@houtworm.net>              //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/10/01 00:57:08 by houtworm     /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/10/16 11:34:29 by houtworm     \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_exec(t_commands cmd, t_shell *msh)
{
	int		i;
	int		status;
	char	**paths;
	char	**args;

	i = 0;
	paths = ft_getpaths(msh->envp, 1);
	args = ft_calloc(1000, 8);
	while (cmd.arg[i + 1])
	{
		args[i] = ft_strdup(cmd.arg[i + 1]);
		i++;
	}
	free(cmd.absolute);
	cmd.absolute = ft_abspathcmd(paths, args[0]);
	ft_frearr(paths);
	status = ft_checkcommand(args, msh->envp);
	if (status)
		status = 127;
	else
		execve(cmd.absolute, args, msh->envp);
	ft_frearr(args);
	free(cmd.absolute);
	return (status);
}
