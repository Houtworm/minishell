/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   verify.c                                        |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: houtworm <codam@houtworm.net>              //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/08/25 04:55:07 by houtworm     /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/10/16 12:28:01 by houtworm     \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_checkinputfile(char *file)
{
	if (file)
	{
		if (access(file, R_OK) < 0)
		{
			if (access(file, F_OK) < 0)
				return (ft_errorret("no such file or directory", file, 1));
			return (ft_errorret("permission denied", file, 1));
		}
	}
	return (0);
}

int	ft_checkoutputfile(char *file)
{
	int		i;

	i = ft_strlen(file) - 1;
	if (file)
	{
		if (access(file, F_OK) < 0)
		{
			while (i > 0 && file[i] != '/')
			{
				file[i] = '\0';
				i--;
			}
			if (i == 0)
				return (ft_errorret("is a directory", file, 1));
			if (!file)
				file[i] = '\0';
			if (access(file, F_OK) < 0)
				return (ft_errorret("no such file or directory", file, 1));
		}
		else if (access(file, W_OK) < 0)
		{
			return (ft_errorret("permission denied", file, 1));
		}
	}
	return (0);
}

int	ft_checkcommand(char **args, char **envp)

{
	int		i;
	char	*temp;
	char	**paths;

	i = 0;
	paths = ft_getpaths(envp, 1);
	if (args[0] && ft_chrstr('/', args[0]))
		temp = ft_strjoin(NULL, args[0]);
	else
	{
		if (!paths)
			return (ft_errorret("command not found", args[0], 127));
		temp = ft_strjoin(paths[i], args[0]);
	}
	while (access(temp, F_OK) && paths[i] && !ft_chrstr('/', args[0]))
	{
		free(temp);
		i++;
		temp = ft_strjoin(paths[i], args[0]);
	}
	if (!paths[i] || ft_isallbyte(args[0], ' ') || ft_isallbyte(args[0], '.') || access(temp, F_OK))
	{
		free (temp);
		ft_frearr(paths);
		return (ft_errorret("command not found", args[0], 127));
	}
	ft_frearr(paths);
	if (access(temp, X_OK))
	{
		free (temp);
		return (ft_errorret("permission denied", args[0], 126));
	}
	free (temp);
	return (0);
}
