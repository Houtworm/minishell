/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   period.c                                        |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: houtworm <codam@houtworm.net>              //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/09/30 04:01:18 by houtworm     /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/10/01 21:02:36 by houtworm     \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_checkperiod(t_cmds cmds)
{
	int		i;
	DIR		*dir;

	i = 0;
	dir = opendir(cmds.arguments[0]);
	if (dir || errno == EACCES)
	{
		ft_errorexit("Is a directory", cmds.arguments[0], 0);
		return (126);
	}
	if (access(cmds.arguments[0], F_OK))
		if (ft_errorexit("No such file or directory", cmds.arguments[0], 0))
			i = 127;
	if ((access(cmds.arguments[0], X_OK) || access(cmds.arguments[0], R_OK)) && i != 127)
		if (ft_errorexit("permission denied", cmds.arguments[0], 0))
			i = 126;
	if (i == 127 || i == 126)
		return (i);
	return (0);
}

int	ft_period(t_cmds cmds)
{
	int		status;

	if (cmds.arguments[0][1] == '\0')
	{
		if (ft_errorexit("filename argument required", ".", 0))
			return (2);
	}
	else if (cmds.arguments[0][1] == '/' || cmds.arguments[0][0] == '/')
	{
		status = ft_checkperiod(cmds);
		if (status)
			return (status);
		execve(cmds.absolute, cmds.arguments, cmds.envp);
		exit(-1);
	}
	else
	{
		if (ft_errorexit("command not found", cmds.arguments[0], 0))
			return (127);
	}
	return (0);
}
