/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   verify.c                                        |o_o || |                */
/*                                                     +:+                    */
/*   By: houtworm <codam@houtworm.net>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/25 04:55:07 by houtworm      #+#    #+#                 */
/*   Updated: 2023/10/17 20:46:54 by houtworm     \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_checkinputfile(char *file)
{
	int		fd;

	if (file)
	{
		fd = open(file, O_RDWR);
		if (errno == EISDIR) 
			return (ft_errorret("is a directory", file, 1));
		close(fd);
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
	int		fd;

	i = ft_strlen(file) - 1;
	if (file)
	{
		
		if (file[0] == '\0')
			return (ft_errorret("no such file or directory", file, 1));
		fd = open(file, O_RDONLY | O_CREAT);
		close(fd);
		if (access(file, F_OK) < 0)
		{
			if (ft_chrstr('/', file))
			{
				while (i > 0 && file[i] != '/')
				{
					file[i] = '\0';
					i--;
				}
				file[i] = '\0';
				if (access(file, F_OK) < 0)
					return (ft_errorret("no such file or directory", file, 1));
			}
			else
				return (ft_errorret("is a directory", file, 1));
		}
		else if (access(file, W_OK) < 0)
		{
			return (ft_errorret("permission denied", file, 1));
		}
		else if (fd == -1) 
			return (ft_errorret("is a directory", file, 1));
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
