/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   ft_system.c                                     |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: houtworm <codam@houtworm.net>              //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/03/20 16:39:22 by houtworm     /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/03/24 16:57:09 by djonker      \___)=(___/                 */
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
	pid = read(fd, command, 2000);
	close(fd);
	command[pid - 1] = '\0';
	ft_frearr(paths);
	ft_frearr(cmd);
	return (command);
}
