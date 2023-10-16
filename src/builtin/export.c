/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                        |o_o || |                */
/*                                                    +:+ +:+         +:+     */
/*   By: houtworm <codam@houtworm.net>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 18:12:44 by houtworm          #+#    #+#             */
/*   Updated: 2023/10/16 10:59:14 by houtworm     \___)=(___/                 */
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

int	ft_export(t_commands cmd, t_shell *shell)
{
	char	**envp;
	char	*var;
	char	*val;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!cmd.arg[1])
	{
		ft_printexport();
		return (0);
	}
	if (cmd.arg[1][0] == '-')
	{
		return (ft_errorret("invalid option", "export", 2));
	}
	if ((cmd.arg[1][i] < 'a' || cmd.arg[1][i] > 'z') && (cmd.arg[1][i] < 'A' || cmd.arg[1][i] > 'Z'))
		if (cmd.arg[1][i] != '_')
			return (ft_errorret2("not a valid identifier", cmd.arg[1], "export", 1));
	var = ft_calloc(512, 1);
	val = ft_calloc(512, 1);
	while (cmd.arg[1][i] != '\0' && cmd.arg[1][i] != '=')
	{
		if ((cmd.arg[1][i] < 'a' || cmd.arg[1][i] > 'z') && (cmd.arg[1][i] < 'A' || cmd.arg[1][i] > 'Z'))
			if (cmd.arg[1][i] != '_' && cmd.arg[1][i] < '0' && cmd.arg[1][i] > '9')
			{
				ft_vafree(2, var, val);
				return (ft_errorret2("not a valid identifier", cmd.arg[1], "export", 1));
			}
		var[i] = cmd.arg[1][i];
		i++;
	}
	if (!i || (cmd.arg[2] && cmd.arg[2][0] == '='))
	{
		ft_vafree(2, var, val);
		return (ft_errorret("not a valid identifier", "export", 1));
	}
	while (cmd.arg[1][i + j + 1] != '\0')
	{
		val[j] = cmd.arg[1][1 + j + i];
		j++;
	}
	envp = ft_setenv(shell->envp, var, val);
	ft_charpptofd(envp, shell->envpfd);
	ft_vafree(2, var, val);
	return (0);
}
