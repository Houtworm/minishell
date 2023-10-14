/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   which.c                                         |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: houtworm <codam@houtworm.net>              //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/09/30 04:03:34 by houtworm     /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/10/14 05:53:38 by djonker      \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*int	ft_which(t_cmds cmds, t_shell *shell)*/
/*{*/
	/*char	*absolute;*/
	/*char	**paths;*/

	/*if (!cmds.arguments[1])*/
		/*return (ft_errorreturn("which command", "Usage", -1));*/
	/*paths = ft_getpaths(shell->envp, 0);*/
	/*absolute = ft_abspathcmd(paths, cmds.arguments[1]);*/
	/*ft_frearr(paths);*/
	/*if (absolute[0] != '/' || cmds.arguments[1][0] == '.')*/
	/*{*/
		/*ft_putstr_fd("which: no ", 2);*/
		/*ft_putstr_fd(absolute, 2);*/
		/*ft_putendl_fd(" in paths", 2);*/
		/*free(absolute);*/
		/*return (1);*/
	/*}*/
	/*printf("%s\n", absolute);*/
	/*free(absolute);*/
	/*return (0);*/
/*}*/

int	ft_which(t_cmds cmds, t_shell *shell)
{
	char	*absolute;
	char	**paths;
	int		i;
	char	*str;

	if (!cmds.arguments[1])
		if (ft_errorexit("which command", "Usage", 0))
			return (-1);
	while (i < 13)
	{
		if (!ft_strncmp(cmds.arguments[1], shell->builtins[i].compare, 6))
		{
			str = ft_strjoin(shell->builtins[i].compare, ": shell built-in command");
			ft_putendl(str);
			free(str);
			return (0);
		}
		i++;
	}
	paths = ft_getpaths(shell->envp, 0);
	absolute = ft_abspathcmd(paths, cmds.arguments[1]);
	if (absolute[0] != '/')
	{
		str = ft_vastrjoin(3, "which: no ", absolute, " in paths");
		ft_frearr(paths);
		free(absolute);
		ft_putendl(str);
		free(str);
		return (1);
	}
	ft_frearr(paths);
	printf("%s\n", absolute);
	free(absolute);
	return (0);
}
