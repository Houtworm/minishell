/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_system.c                                     |o_o || |                */
/*                                                     +:+                    */
/*   By: houtworm <codam@houtworm.net>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/20 16:39:22 by houtworm      #+#    #+#                 */
/*   Updated: 2023/10/09 08:16:18 by houtworm     \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_system(char *command, char **envp)
{
	char	**cmd;
	char	**paths;
	int		pid;
	int		fd;

	cmd = ft_split(command, ' ');
	paths = ft_getpaths(envp, pid);
	if (!paths)
	{
		command = ft_strdup(cmd[0]);
		ft_frearr(cmd);
		return (command);
	}
	command = ft_abspathcmd(paths, cmd[0]);
	pid = fork();
	if (pid == 0)
	{
		fd = open("/tmp/ft_systemtmpfile", O_RDWR | O_CREAT | O_TRUNC, 0666);
		dup2(fd, 1);
		execve(command, cmd, envp);
	}
	waitpid(pid, NULL, 0);
	free(command);
	command = ft_calloc(8 * 2000, 1);
	fd = open("/tmp/ft_systemtmpfile", O_RDONLY);
	pid = read(fd, command, 1000);
	close(fd);
	command[pid - 1] = '\0';
	ft_frearr(paths);
	ft_frearr(cmd);
	return (command);
}
