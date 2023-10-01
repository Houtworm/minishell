/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   builtin.c                                       |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: houtworm <codam@houtworm.net>              //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/09/12 15:11:33 by houtworm     /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/10/02 01:41:24 by houtworm     \___)=(___/                 */
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
	int	status;
	int	fd;
	char	*line;
	t_builtin	bui[13] = {
	{"alias\0", ft_echo},
	{"echo\0", ft_echo},
	{"env\0", ft_env},
	{"export\0", ft_export},
	{"unset\0", ft_unset},
	{"pwd\0", ft_pwd},
	{".\0", ft_period},
	{"/\0", ft_period},
	{"which\0", ft_which},
	{"cd\0", ft_chdir},
	{"exit\0", ft_exit},
	{"exec\0", ft_exec},
	{"z\0", ft_z}
	};

	i = 0;
	while (i < 9)
	{
		if (!ft_strncmp(cmds.arguments[0], bui[i].compare, ft_strlen(bui[i].compare)))
		{
			pid = fork();
			if (pid == 0)
			{
				ft_dupmachine(cmds, cmdnbr, forknbr, shell);
				ret = bui[i].func(cmds);
				if (ret == 123)
				{
					status = 1;
					fd = open(cmds.absolute, O_RDONLY);
					while (status > 0)
					{
						status = get_next_line(fd, &line);
						if (line[0] && ft_parseline(line, shell))
							exit (2);
						if (status > 0)
							shell->code = ft_forktheforks(shell);
						free(line);
					}
					exit(shell->code);
				}
				exit(ret);
			}
			waitpid(pid, &ret, 0);
			shell->code = WEXITSTATUS(ret);
			return (shell->code);
		}
		i++;
	}
	while (i < 13)
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
