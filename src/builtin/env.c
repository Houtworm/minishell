/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                           |o_o || |                */
/*                                                    +:+ +:+         +:+     */
/*   By: houtworm <codam@houtworm.net>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 18:13:16 by houtworm          #+#    #+#             */
/*   Updated: 2023/10/05 06:47:38 by houtworm     \___)=(___/                 */
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
			ft_moderrorexit(cmds.arguments[1], "env", "invalid option", 125);
		else
			ft_moderrorexit("No such file or directory", "env", cmds.arguments[1], 127);
	}
	if (cmds.arguments[0][3] == ' ')
		ft_moderrorexit("command not found", "env", cmds.arguments[1], 127);
	fd = open("/tmp/minishellenvpfile.tmp", O_RDONLY);
	status = get_next_line(fd, &line);
	while (status > 0)
	{
		ft_putendl(line);
		free(line);
		status = get_next_line(fd, &line);
	}
	close(fd);
	exit (0);
	shell = shell;
}
