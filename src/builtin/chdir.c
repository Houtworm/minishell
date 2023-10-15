/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   chdir.c                                         |o_o || |                */
/*                                                     +:+                    */
/*   By: djonker <djonker@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/18 17:21:02 by djonker       #+#    #+#                 */
/*   Updated: 2023/10/15 05:37:42 by houtworm     \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_adddirtoz(char *cwd, char **envp)
{
	int		mshzfd;
	int		tempfd;
	char	*line;
	char	*home;

	line = ft_gethome(envp);
	home = ft_strjoin(line, "/.mshz");
	mshzfd = open(home, O_RDONLY);
	tempfd = open("/tmp/minishell/tempz.tmp", O_RDWR | O_CREAT | O_TRUNC, 0666);
	free(line);
	ft_putendl_fd(cwd, tempfd);
	while (get_next_line(mshzfd, &line) > 0)
	{
		if (ft_strncmp(line, cwd, 500))
			ft_putendl_fd(line, tempfd);
		free(line);
	}
	free(line);
	close(tempfd);
	close(mshzfd);
	tempfd = open("/tmp/minishell/tempz.tmp", O_RDONLY);
	mshzfd = open(home, O_RDWR | O_CREAT | O_TRUNC, 0666);
	while (get_next_line(tempfd, &line) > 0)
	{
		ft_putendl_fd(line, mshzfd);
		free(line);
	}
	free(line);
	free(home);
	close(mshzfd);
	close(tempfd);
}

int	ft_chdir(t_cmds cmds, t_shell *shell)
{
	char	*line;
	char	*newcwd;
	char	*oldcwd;

	if (cmds.arguments[2])
		return (ft_errorreturn("too many arguments", "cd", 1));
	if (!cmds.arguments[1] || cmds.arguments[1][0] == '\0')
	{
		newcwd = ft_getuser(shell->envp);
		line = ft_vastrjoin(3, "/home/", newcwd, "/");
		free(newcwd);
	}
	else if (!ft_strncmp(cmds.arguments[1],  "-\0", 2))
	{
		line = ft_getenvval(shell->envp, "OLDPWD");
		if (!line)
			return (ft_errorreturn("OLDPWD not set", "cd", 1));
		printf("%s\n", line);
	}
	else
	{
		line = ft_strdup(cmds.arguments[1]);
	}
	oldcwd = malloc(512);
	getcwd(oldcwd, 512);
	if (chdir(line))
	{
		free(oldcwd);
		free(line);
		if (errno == ENOTDIR)
			return (ft_moderrorreturn("Not a directory", cmds.arguments[0], cmds.arguments[1], 1));
		else
			return (ft_moderrorreturn("No such file or directory", cmds.arguments[0], cmds.arguments[1], 1));
		return (1);
	}
	free(line);
	if (oldcwd[0] == '/')
		ft_setenv(shell->envp, "OLDPWD", oldcwd);
	free(oldcwd);
	newcwd = malloc(512);
	getcwd(newcwd, 512);
	if (newcwd[0] != '/')
	{
		free(newcwd);
		line = ft_getuser(shell->envp);
		newcwd = ft_vastrjoin(3, "/home/", line, "/");
		free(line);
		chdir(newcwd);
		ft_moderrorreturn("No such file or directory Seems the current directory does not exist, going home", cmds.arguments[0], cmds.arguments[1], 1);
	}
	ft_setenv(shell->envp, "PWD", newcwd);
	ft_adddirtoz(newcwd, shell->envp);
	free(newcwd);
	ft_charpptofd(shell->envp, shell->envpfd);
	return (0);
}
