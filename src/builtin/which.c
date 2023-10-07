/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   which.c                                         |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: houtworm <codam@houtworm.net>              //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/09/30 04:03:34 by houtworm     /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/10/07 02:50:39 by djonker      \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_which(t_cmds cmds, t_shell *shell)
{
	char	*absolute;
	char	**paths;

	if (!cmds.arguments[1])
		return (ft_errorreturn("which command", "Usage", -1));
	paths = ft_getpaths(shell->envp, 0);
	absolute = ft_abspathcmd(paths, cmds.arguments[1]);
	ft_frearr(paths);
	if (absolute[0] != '/' || cmds.arguments[1][0] == '.')
	{
		ft_putstr_fd("which: no ", 2);
		ft_putstr_fd(absolute, 2);
		ft_putendl_fd(" in paths", 2);
		free(absolute);
		return (1);
	}
	printf("%s\n", absolute);
	free(absolute);
	return (0);
}

/*int	ft_which(t_cmds cmds)*/
/*{*/
	/*char	*absolute;*/
	/*char	**paths;*/

	/*if (!cmds.arguments[1])*/
		/*if (ft_errorexit("which command", "Usage", 0))*/
			/*return (-1);*/
	/*if (!ft_strncmp(cmds.arguments[1], "alias\0", 6))*/
		/*absolute = ft_strdup("alias: shell built-in command");*/
	/*else if (!ft_strncmp(cmds.arguments[1], "echo\0", 5))*/
		/*absolute = ft_strdup("echo: shell built-in command");*/
	/*else if (!ft_strncmp(cmds.arguments[1], "env\0", 4))*/
		/*absolute = ft_strdup("env: shell built-in command");*/
	/*else if (!ft_strncmp(cmds.arguments[1], "export\0", 7))*/
		/*absolute = ft_strdup("export: shell built-in command");*/
	/*else if (!ft_strncmp(cmds.arguments[1], "unset\0", 6))*/
		/*absolute = ft_strdup("unset: shell built-in command");*/
	/*else if (!ft_strncmp(cmds.arguments[1], ".\0", 2))*/
		/*absolute = ft_strdup(".: shell built-in command");*/
	/*else if (!ft_strncmp(cmds.arguments[1], "which\0", 6))*/
		/*absolute = ft_strdup("which: shell built-in command");*/
	/*else if (!ft_strncmp(cmds.arguments[1], "cd\0", 3))*/
		/*absolute = ft_strdup("cd: shell built-in command");*/
	/*else if (!ft_strncmp(cmds.arguments[1], "exit\0", 5))*/
		/*absolute = ft_strdup("exit: shell built-in command");*/
	/*else if (!ft_strncmp(cmds.arguments[1], "z\0", 2))*/
		/*absolute = ft_strdup("z: shell built-in command");*/
	/*else*/
	/*{*/
		/*paths = ft_getpaths(cmds.envp, 0);*/
		/*absolute = ft_abspathcmd(paths, cmds.arguments[1]);*/
		/*if (absolute[0] != '/')*/
		/*{*/
			/*ft_putstr_fd("which: no ", 2);*/
			/*ft_putstr_fd(absolute, 2);*/
			/*ft_putendl_fd(" in paths", 2);*/
			/*ft_frearr(paths);*/
			/*free(absolute);*/
			/*return (1);*/
		/*}*/
		/*ft_frearr(paths);*/
	/*}*/
	/*printf("%s\n", absolute);*/
	/*free(absolute);*/
	/*return (0);*/
/*}*/
