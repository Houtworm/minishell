/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   exec.c                                          |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: houtworm <codam@houtworm.net>              //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/10/01 00:57:08 by houtworm     /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/10/02 15:48:58 by houtworm     \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

typedef struct	s_builtin
{
	char	*compare;
	int		(*func)(t_cmds cmds);
}	t_builtin;

int	ft_builtincheckexec(t_cmds cmds)
{
	int	pid;
	int	ret;
	int i;
	t_builtin	bui[12] = {
	{"alias\0", ft_echo},
	{"echo\0", ft_echo},
	{"env\0", ft_env},
	{"export\0", ft_export},
	{"unset\0", ft_unset},
	{".\0", ft_period},
	{"/\0", ft_period},
	{"which\0", ft_which},
	{"cd\0", ft_chdir},
	{"exit\0", ft_exit},
	{"exec\0", ft_exec},
	{"z\0", ft_z}
	};

	i = 0;
	while (i < 8)
	{
		if (!ft_strncmp(cmds.arguments[0], bui[i].compare, ft_strlen(bui[i].compare)))
		{
			pid = fork();
			if (pid == 0)
			{
				exit (bui[i].func(cmds));
			}
			waitpid(pid, &ret, 0);
			exit (WEXITSTATUS(ret));
		}
		i++;
	}
	while (i < 12)
	{
		if (!ft_strncmp(cmds.arguments[0], bui[i].compare, ft_strlen(bui[i].compare) + 1))
		{
			exit (bui[i].func(cmds));
		}
		i++;
	}
	return (-1111);
}

int	ft_exec(t_cmds cmds)
{
	int		i;
	int		status;
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
	status = ft_checkcommand(cmds);
	if (status)
		return (status);
	execve(cmds.absolute, cmds.arguments, cmds.envp);
	exit (ft_errorexit("command not found", cmds.absolute, 127));
}
