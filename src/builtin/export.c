/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                        |o_o || |                */
/*                                                    +:+ +:+         +:+     */
/*   By: houtworm <codam@houtworm.net>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 18:12:44 by houtworm          #+#    #+#             */
/*   Updated: 2023/10/02 00:42:21 by houtworm     \___)=(___/                 */
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
	while (cmds.arguments[1][i] != '\0' && cmds.arguments[1][i] != '=')
	{
		var[i] = cmds.arguments[1][i];
		i++;
	}
	if (!i)
		if (ft_errorexit("not a valid identifier", "export", 0))
			return (1);
	/*if (cmds.arguments[1][i] != '=')*/
		/*if (ft_errorexit("not a valid identifier", "export", 0))*/
			/*return (1);*/
	while (cmds.arguments[1][i + j + 1] != '\0')
	{
		val[j] = cmds.arguments[1][1 + j + i];
		j++;
	}
	ft_setenv(cmds.envp, var, val);
	free(var);
	free(val);
	ft_charpptofd(cmds.envp, cmds.envpfd);
	return (0);
}
