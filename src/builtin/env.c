/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env.c                                           |o_o || |                */
/*                                                     +:+                    */
/*   By: houtworm <codam@houtworm.net>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/21 18:13:16 by houtworm      #+#    #+#                 */
/*   Updated: 2023/10/09 04:14:04 by houtworm     \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_env(t_cmds cmds, t_shell *shell)
{
	int		status;
	int		fd;
	char	*line;

	if (cmds.arguments[1])
	{
		if (cmds.arguments[1][0] == '-')
			return (ft_moderrorreturn(cmds.arguments[1], "env", "invalid option", 125));
		else
			return (ft_moderrorreturn("No such file or directory", "env", cmds.arguments[1], 127));
	}
	if (cmds.arguments[0][3] == ' ')
		return (ft_moderrorreturn("command not found", "env", cmds.arguments[1], 127));
	fd = open("/tmp/minishellenvpfile.tmp", O_RDONLY);
	status = get_next_line(fd, &line);
	while (status > 0)
	{
		ft_putendl(line);
		free(line);
		status = get_next_line(fd, &line);
	}
	free(line);
	close(fd);
	shell = shell;
	return (0);
}
