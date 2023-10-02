/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                        |o_o || |                */
/*                                                    +:+ +:+         +:+     */
/*   By: houtworm <codam@houtworm.net>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 18:12:44 by houtworm          #+#    #+#             */
/*   Updated: 2023/10/02 15:15:36 by houtworm     \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_printexport(void)
{
	int		status;
	int		fd;
	char	*line;

	fd = open("/tmp/minishellenvpfile.tmp", O_RDONLY);
	status = get_next_line(fd, &line);
	while (status > 0)
	{
		ft_putstr("declare -x ");
		ft_putendl(line);
		free(line);
		status = get_next_line(fd, &line);
	}
	close(fd);
	return (0);
}

int	ft_export(t_cmds cmds)
{
	char	*var;
	char	*val;
	int		i;
	int		j;

	i = 0;
	j = 0;
	var = ft_calloc(512, 1);
	val = ft_calloc(512, 1);
	if (!cmds.arguments[1])
	{
		ft_printexport();
		return (0);	
	}
	if (cmds.arguments[1][0] == '-')
		if (ft_errorexit("invalid option", "export", 0))
			return (2);
	if ((cmds.arguments[1][i] < 'a' || cmds.arguments[1][i] > 'z') && (cmds.arguments[1][i] < 'A' || cmds.arguments[1][i] > 'Z'))
		if (cmds.arguments[1][i] != '_')
			if (ft_moderrorexit("not a valid identifier", cmds.arguments[1], "export", 0))
				return (1);
	while (cmds.arguments[1][i] != '\0' && cmds.arguments[1][i] != '=')
	{
		if ((cmds.arguments[1][i] < 'a' || cmds.arguments[1][i] > 'z') && (cmds.arguments[1][i] < 'A' || cmds.arguments[1][i] > 'Z'))
			if (cmds.arguments[1][i] != '_' && cmds.arguments[1][i] < '0' && cmds.arguments[1][i] > '9')
				if (ft_moderrorexit("not a valid identifier", cmds.arguments[1], "export", 0))
					return (1);
		var[i] = cmds.arguments[1][i];
		i++;
	}
	if (!i || (cmds.arguments[2] && cmds.arguments[2][0] == '='))
		if (ft_errorexit("not a valid identifier", "export", 0))
			return (1);
	while (cmds.arguments[1][i + j + 1] != '\0')
	{
		val[j] = cmds.arguments[1][1 + j + i];
		j++;
	}
	cmds.envp = ft_setenv(cmds.envp, var, val);
	ft_charpptofd(cmds.envp, cmds.envpfd);
	free(var);
	free(val);
	return (0);
}
