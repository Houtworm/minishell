/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   verify.c                                        |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: houtworm <codam@houtworm.net>              //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/08/25 04:55:07 by houtworm     /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/08/25 04:55:42 by houtworm     \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_checkfiles(int argc, char **argv, int file)
{
	if (!file)
	{
		if (ft_strncmp(argv[1], "here_doc", 9))
		{
			if (access(argv[1], R_OK) < 0)
			{
				if (access(argv[1], F_OK) < 0)
					ft_errorexit("no such file or directory", argv[1], 0);
				else
					ft_errorexit("permission denied", argv[1], 0);
				return (1);
			}
		}
	}
	else
	{
		if (!access(argv[argc - 1], F_OK) && access(argv[argc - 1], W_OK))
		{
			ft_errorexit("permission denied", argv[argc - 1], 0);
			return (1);
		}
	}
	return (0);
}

int	ft_checkcommands(char **current, char **paths, char **cmd, int cmdnbr)
{
	int		i;
	char	*temp;

	i = 0;
	if (current[0] && ft_chrstr('/', current[0]))
		temp = ft_strjoin(NULL, current[0]);
	else
		temp = ft_strjoin(paths[i], current[0]);
	while (access(temp, F_OK) && paths[i] && !ft_chrstr('/', current[0]))
	{
		free(temp);
		i++;
		temp = ft_strjoin(paths[i], current[0]);
	}
	if (!paths[i] || ft_isallbyte(cmd[cmdnbr], ' ') || access(temp, F_OK))
		if (ft_errorexit("command not found", cmd[cmdnbr], 0))
			i = 127;
	if (access(temp, X_OK) && i != 127)
		if (ft_errorexit("permission denied", current[0], 0))
			i = 126;
	free (temp);
	return (i);
}
