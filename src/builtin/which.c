/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   which.c                                         |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: houtworm <codam@houtworm.net>              //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/09/30 04:03:34 by houtworm     /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/10/16 12:14:34 by houtworm     \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_whichcheckbuiltin(t_commands cmd, t_shell *msh)
{
	int		i;
	char	*str;

	i = 0;
	while (i < 13)
	{
		if (!ft_strncmp(cmd.arg[1], msh->bltn[i].cmnd, 6))
		{
			str = ft_strjoin(msh->bltn[i].cmnd, ": msh built-in command");
			ft_putendl(str);
			free(str);
			return (1);
		}
		i++;
	}
	return (0);
}

int	ft_whichcheckpath(t_commands cmd, t_shell *msh)
{
	char	*absolute;
	char	**paths;
	char	*str;

	paths = ft_getpaths(msh->envp, 0);
	absolute = ft_abspathcmd(paths, cmd.arg[1]);
	if (absolute[0] != '/')
	{
		str = ft_vastrjoin(3, "which: no ", absolute, " in paths");
		ft_frearr(paths);
		free(absolute);
		ft_putendl(str);
		free(str);
		return (0);
	}
	ft_frearr(paths);
	ft_putendl(absolute);
	free(absolute);
	return (1);
}

int	ft_which(t_commands cmd, t_shell *msh)
{
	if (!cmd.arg[1])
		if (ft_errorexit("which command", "Usage", 0))
			return (-1);
	if (ft_whichcheckbuiltin(cmd, msh))
		return (0);
	if (ft_whichcheckpath(cmd, msh))
		return (0);
	return (1);
}
