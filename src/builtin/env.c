/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env.c                                           |o_o || |                */
/*                                                     +:+                    */
/*   By: houtworm <codam@houtworm.net>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/21 18:13:16 by houtworm      #+#    #+#                 */
/*   Updated: 2023/10/16 10:45:58 by houtworm     \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_env(t_commands cmd, t_shell *shell)
{
	int		status;
	int		fd;
	char	*line;

	if (cmd.arg[1])
	{
		if (cmd.arg[1][0] == '-')
			return (ft_errorret2(cmd.arg[1], "env", "invalid option", 125));
		else
			return (ft_errorret2("No such file or directory", "env", cmd.arg[1], 127));
	}
	if (cmd.arg[0][3] == ' ')
		return (ft_errorret2("command not found", "env", cmd.arg[1], 127));
	fd = open("/tmp/minishell/envpfile.tmp", O_RDONLY);
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
