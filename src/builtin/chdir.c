/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   chdir.c                                         |o_o || |                */
/*                                                     +:+                    */
/*   By: djonker <djonker@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/18 17:21:02 by djonker       #+#    #+#                 */
/*   Updated: 2023/10/18 04:38:01 by houtworm     \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_writezfile(char *home, char *tmpfile)
{
	int		mshzfd;
	int		tempfd;
	char	*line;

	tempfd = open(tmpfile, O_RDONLY);
	mshzfd = open(home, O_RDWR | O_CREAT | O_TRUNC, 0666);
	while (get_next_line(tempfd, &line) > 0)
	{
		ft_putendl_fd(line, mshzfd);
		free(line);
	}
	free(line);
	free(home);
	free(tmpfile);
	close(mshzfd);
	close(tempfd);
}

void	ft_adddirtoz(char *cwd, t_shell *msh)
{
	int		mshzfd;
	int		tempfd;
	char	*tmpfile;
	char	*line;
	char	*home;

	line = ft_gethome(msh->envp);
	home = ft_strjoin(line, "/.mshz");
	free(line);
	mshzfd = open(home, O_RDONLY);
	tmpfile = ft_strjoin(msh->tmpdir, "tempz.tmp");
	tempfd = open(tmpfile, O_RDWR | O_CREAT | O_TRUNC, 0666);
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
	ft_writezfile(home, tmpfile);
}

int	ft_cdgetoldcwd(t_commands cmd, t_shell *msh, char *line)
{
	char	*oldcwd;

	oldcwd = malloc(512);
	getcwd(oldcwd, 512);
	if (chdir(line))
	{
		free(oldcwd);
		free(line);
		if (errno == ENOTDIR)
			return (ft_errorret2("Not a directory", cmd.arg[0], cmd.arg[1], 1));
		else
			return (ft_errorret2("No such file or directory", cmd.arg[0], cmd.arg[1], 1));
		return (1);
	}
	free(line);
	if (oldcwd[0] == '/')
		ft_setenv(msh->envp, "OLDPWD", oldcwd);
	free(oldcwd);
	return (0);
}

void	ft_cdgetnewcwd(t_commands cmd, t_shell *msh)
{
	char	*newcwd;
	char	*line;

	newcwd = malloc(512);
	getcwd(newcwd, 512);
	if (newcwd[0] != '/')
	{
		free(newcwd);
		line = ft_getuser(msh->envp);
		newcwd = ft_vastrjoin(3, "/home/", line, "/");
		free(line);
		chdir(newcwd);
		ft_errorret2("No such file or directory Seems the current directory does not exist, going home", cmd.arg[0], cmd.arg[1], 1);
	}
	ft_setenv(msh->envp, "PWD", newcwd);
	ft_adddirtoz(newcwd, msh);
	free(newcwd);
	ft_charpptofd(msh->envp, msh);
}
int	ft_chdir(t_commands cmd, t_shell *msh)
{
	char	*line;
	char	*temp;

	if (cmd.arg[2])
		return (ft_errorret("too many arguments", "cd", 1));
	if (!cmd.arg[1] || cmd.arg[1][0] == '\0')
	{
		temp = ft_getuser(msh->envp);
		line = ft_vastrjoin(3, "/home/", temp, "/");
		free(temp);
	}
	else if (!ft_strncmp(cmd.arg[1],  "-\0", 2))
	{
		line = ft_getenvval(msh->envp, "OLDPWD");
		if (!line)
			return (ft_errorret("OLDPWD not set", "cd", 1));
		printf("%s\n", line);
	}
	else
		line = ft_strdup(cmd.arg[1]);
	if (ft_cdgetoldcwd(cmd, msh, line))
		return (1);
	ft_cdgetnewcwd(cmd, msh);
	return (0);
}
