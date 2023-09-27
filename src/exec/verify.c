/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   verify.c                                        |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: houtworm <codam@houtworm.net>              //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/08/25 04:55:07 by houtworm     /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/09/27 12:00:53 by djonker      \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_checkinputfile(char *inputfile)
{
	if (inputfile)
	{
		if (access(inputfile, R_OK) < 0)
		{
			if (access(inputfile, F_OK) < 0)
				ft_errorexit("no such file or directory", inputfile, 0);
			else
				ft_errorexit("permission denied", inputfile, 0);
			return (1);
		}
	}
	return (0);
}

int	ft_checkoutputfile(char *outputfile)
{
	if (outputfile)
	{
		if (!access(outputfile, F_OK) && access(outputfile, W_OK))
		{
			ft_errorexit("permission denied", outputfile, 0);
			return (1);
		}
	}	
	return (0);
}

int	ft_checkcommand(t_cmds cmds)
{
	int		i;
	char	*temp;
	char	**paths;

	i = 0;
	paths = ft_getpaths(cmds.envp, 1);
	if (cmds.arguments[0] && ft_chrstr('/', cmds.arguments[0]))
		temp = ft_strjoin(NULL, cmds.arguments[0]);
	else
		temp = ft_strjoin(paths[i], cmds.arguments[0]);
	while (access(temp, F_OK) && paths[i] && !ft_chrstr('/', cmds.arguments[0]))
	{
		free(temp);
		i++;
		temp = ft_strjoin(paths[i], cmds.arguments[0]);
	}
	if (!paths[i] || ft_isallbyte(cmds.arguments[0], ' ') || ft_isallbyte(cmds.arguments[0], '.') || access(temp, F_OK))
	{
		if (ft_errorexit("command not found", cmds.arguments[0], 0))
			i = 127;
	}
	if (access(temp, X_OK) && i != 127)
	{
		if (ft_errorexit("permission denied", cmds.arguments[0], 0))
			i = 126;
	}
	free (temp);
	if (i == 127 || i == 126)
		return (i);
	return (0);
}
