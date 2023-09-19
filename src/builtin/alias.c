/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   alias.c                                         |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: houtworm <codam@houtworm.net>              //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/09/20 00:06:19 by houtworm     /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/09/20 00:38:21 by houtworm     \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_printalias(void)
{
	int		status;
	int		fd;
	char	*line;

	fd = open("/tmp/minishellenvpfile.tmp", O_RDONLY);
	status = get_next_line(fd, &line);
	while (status > 0)
	{
		ft_putendl(line);
		free(line);
		status = get_next_line(fd, &line);
	}
	close(fd);
	return (0);
}

int	ft_alias(t_cmds cmd)
{
	char	*var;
	char	*val;
	int		i;
	int		j;

	i = 0;
	j = 0;
	var = ft_calloc(512, 1);
	val = ft_calloc(512, 1);
	if (!cmd.arguments[1])
	{
		ft_printalias();
		return (0);	
	}
	while (cmd.arguments[1][i] != '\0' && cmd.arguments[1][i] != '=')
	{
		var[i] = cmd.arguments[1][i];
		i++;
	}
	if (cmd.arguments[1][i] != '=')
		return (1);
	while (cmd.arguments[1][i + j + 1] != '\0')
	{
		val[j] = cmd.arguments[1][1 + j + i];
		j++;
	}
	ft_setenv(cmd.envp, var, val);
	free(var);
	free(val);
	ft_charpptofd(cmd.envp, cmd.envpfd);
	return (0);
}
