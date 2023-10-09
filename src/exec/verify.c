/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   verify.c                                        |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: houtworm <codam@houtworm.net>              //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/08/25 04:55:07 by houtworm     /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/10/09 07:29:09 by houtworm     \___)=(___/                 */
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
				return (ft_errorreturn("no such file or directory", inputfile, 1));
			else
				return (ft_errorreturn("permission denied", inputfile, 1));
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
			return (ft_errorreturn("permission denied", outputfile, 1));
		}
	}	
	return (0);
}

int	ft_checkcommand(t_cmds cmds, char **envp)
{
	int		i;
	char	*temp;
	char	**paths;

	i = 0;
	paths = ft_getpaths(envp, 1);
	if (cmds.arguments[0] && ft_chrstr('/', cmds.arguments[0]))
		temp = ft_strjoin(NULL, cmds.arguments[0]);
	else
	{
		if (!paths)
			return (ft_errorreturn("command not found", cmds.arguments[0], 127));
		temp = ft_strjoin(paths[i], cmds.arguments[0]);
	}
	while (access(temp, F_OK) && paths[i] && !ft_chrstr('/', cmds.arguments[0]))
	{
		free(temp);
		i++;
		temp = ft_strjoin(paths[i], cmds.arguments[0]);
	}
	if (!paths[i] || ft_isallbyte(cmds.arguments[0], ' ') || ft_isallbyte(cmds.arguments[0], '.') || access(temp, F_OK))
	{
		free (temp);
		ft_frearr(paths);
		return (ft_errorreturn("command not found", cmds.arguments[0], 127));
	}
	ft_frearr(paths);
	if (access(temp, X_OK))
	{
		free (temp);
		return (ft_errorreturn("permission denied", cmds.arguments[0], 126));
	}
	free (temp);
	return (0);
}
