/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                        |o_o || |                */
/*                                                    +:+ +:+         +:+     */
/*   By: houtworm <codam@houtworm.net>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 18:12:44 by houtworm          #+#    #+#             */
/*   Updated: 2023/10/15 05:40:52 by houtworm     \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_printexport(void)
{
	int		status;
	int		fd;
	char	*line;
	int 	i;

	fd = open("/tmp/minishell/envpfile.tmp", O_RDONLY);
	status = get_next_line(fd, &line);
	while (status > 0)
	{
		i = 0;
		ft_putstr("declare -x ");
		while (line[i] && line[i] != '=')
		{
			ft_putchar(line[i]);
			i++;
		}
		ft_putstr("=\"");
		ft_putstr(&line[i + 1]);
		ft_putendl("\"");
		free(line);
		status = get_next_line(fd, &line);
	}
	free(line);
	close(fd);
	return (0);
}

int	ft_export(t_cmds cmds, t_shell *shell)
{
	char	**envp;
	char	*var;
	char	*val;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!cmds.arguments[1])
	{
		ft_printexport();
		return (0);	
	}
	if (cmds.arguments[1][0] == '-')
	{
		return (ft_errorreturn("invalid option", "export", 2));
	}
	if ((cmds.arguments[1][i] < 'a' || cmds.arguments[1][i] > 'z') && (cmds.arguments[1][i] < 'A' || cmds.arguments[1][i] > 'Z'))
		if (cmds.arguments[1][i] != '_')
			return (ft_moderrorreturn("not a valid identifier", cmds.arguments[1], "export", 1));
	var = ft_calloc(512, 1);
	val = ft_calloc(512, 1);
	while (cmds.arguments[1][i] != '\0' && cmds.arguments[1][i] != '=')
	{
		if ((cmds.arguments[1][i] < 'a' || cmds.arguments[1][i] > 'z') && (cmds.arguments[1][i] < 'A' || cmds.arguments[1][i] > 'Z'))
			if (cmds.arguments[1][i] != '_' && cmds.arguments[1][i] < '0' && cmds.arguments[1][i] > '9')
			{
				ft_vafree(2, var, val);
				return (ft_moderrorreturn("not a valid identifier", cmds.arguments[1], "export", 1));
			}
		var[i] = cmds.arguments[1][i];
		i++;
	}
	if (!i || (cmds.arguments[2] && cmds.arguments[2][0] == '='))
	{
		ft_vafree(2, var, val);
		return (ft_errorreturn("not a valid identifier", "export", 1));
	}
	while (cmds.arguments[1][i + j + 1] != '\0')
	{
		val[j] = cmds.arguments[1][1 + j + i];
		j++;
	}
	envp = ft_setenv(shell->envp, var, val);
	ft_charpptofd(envp, shell->envpfd);
	ft_vafree(2, var, val);
	return (0);
}
