/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   chdir.c                                         |o_o || |                */
/*                                                     +:+                    */
/*   By: djonker <djonker@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/18 17:21:02 by djonker       #+#    #+#                 */
/*   Updated: 2023/10/07 00:08:13 by djonker      \___)=(___/                 */
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
	tempfd = open("/tmp/minishelltempz.tmp", O_RDWR | O_CREAT | O_TRUNC, 0666);
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
	tempfd = open("/tmp/minishelltempz.tmp", O_RDONLY);
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
	char	*cwd;

	if (cmds.arguments[2])
		return (ft_errorreturn("too many arguments", "cd", 1));
	if (!cmds.arguments[1] || cmds.arguments[1][0] == '\0')
	{

		cwd = ft_getuser(shell->envp);
		line = ft_vastrjoin(3, "/home/", cwd, "/");
		free(cwd);
	}
	else if (!ft_strncmp(cmds.arguments[1],  "-\0", 2))
	{
		line = ft_getenvval(shell->envp, "OLDPWD");
		printf("%s\n", line);
	}
	else
	{
		line = ft_strdup(cmds.arguments[1]);
	}
	cwd = malloc(512);
	getcwd(cwd, 512);
	if (chdir(line))
	{
		free(cwd);
		free(line);
		if (errno == ENOTDIR)
			ft_moderrorexit("Not a directory", cmds.arguments[0], cmds.arguments[1], 1);
		else
			ft_moderrorexit("No such file or directory", cmds.arguments[0], cmds.arguments[1], 1);
		return (1);
	}
	free(line);
	ft_setenv(shell->envp, "OLDPWD", cwd);
	getcwd(cwd, 512);
	ft_setenv(shell->envp, "PWD", cwd);
	ft_adddirtoz(cwd, shell->envp);
	free(cwd);
	ft_charpptofd(shell->envp, shell->envpfd);
	return (0);
}
