/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   builtin.c                                       |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: houtworm <codam@houtworm.net>              //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/09/12 15:11:33 by houtworm     /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/09/27 06:07:04 by djonker      \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

typedef struct	s_builtin
{
	char	*compare;
	int		(*func)(t_cmds cmds);
}	t_builtin;

int	ft_builtincheck(t_cmds cmds, int cmdnbr, int forknbr, t_shell *shell)
{
	int	pid;
	int	ret;
	int i;
	t_builtin	bui[8] = {
	{"alias\0", ft_echo},
	{"echo\0", ft_echo},
	{"env\0", ft_env},
	{"export\0", ft_export},
	{"unset\0", ft_unset},
	{"cd\0", ft_chdir},
	{"exit\0", ft_exit},
	{"z\0", ft_z}
	};

	i = 0;
	while (i < 5)
	{
		if (!ft_strncmp(cmds.arguments[0], bui[i].compare, ft_strlen(bui[i].compare) + 1))
		{
			pid = fork();
			if (pid == 0)
			{
				ft_dupmachine(cmds, cmdnbr, forknbr, shell);
				exit (bui[i].func(cmds));
			}
			waitpid(pid, &ret, 0);
			shell->code = WEXITSTATUS(ret);
			return (shell->code);
		}
		i++;
	}
	while (i < 8)
	{
		if (!ft_strncmp(cmds.arguments[0], bui[i].compare, ft_strlen(bui[i].compare) + 1))
		{
			shell->code = bui[i].func(cmds);
			return (shell->code);
		}
		i++;
	}
	return (-1111);
}
