/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   builtin.c                                       |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: houtworm <codam@houtworm.net>              //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/09/12 15:11:33 by houtworm     /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/09/15 15:48:38 by djonker      \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

struct	builtin
{
	char	*compare;
	int		(*func)(t_cmds cmds);
};

int	ft_builtincheck(t_cmds cmds, int cmdnbr, int forknbr, t_shell *shell)
{
	int	pid;
	int	ret;
	int i;
	struct builtin	bui[5] = {
	{"alias\0", ft_echo},
	{"echo\0", ft_echo},
	{"env\0", ft_env},
	{"export\0", ft_export},
	{"unset\0", ft_unset}
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
			ret = WEXITSTATUS(ret);
			shell->code = ret;
			return (ret);
		}
		i++;
	}
	if (!ft_strncmp(cmds.arguments[0], "exit\0", 5))
		ft_exit(cmds);
	else if (!ft_strncmp(cmds.arguments[0], "cd\0", 3))
		return (ft_chdir(cmds));
	return (-1111);
}
