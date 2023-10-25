/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   period.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: houtworm <codam@houtworm.net>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/30 04:01:18 by houtworm      #+#    #+#                 */
/*   Updated: 2023/10/25 06:47:53 by djonker       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_checkperiod(t_commands cmd)
{
	DIR		*dir;

	dir = opendir(cmd.arg[0]);
	if (dir || errno == EACCES)
	{
		closedir(dir);
		return (ft_errorret("Is a directory", cmd.arg[0], 126));
	}
	if (access(cmd.arg[0], F_OK))
		return (ft_errorret("No such file or directory", cmd.arg[0], 127));
	if ((access(cmd.arg[0], X_OK) || access(cmd.arg[0], R_OK)))
		return (ft_errorret("permission denied", cmd.arg[0], 126));
	return (0);
}

int	ft_scriptfork(t_shell *msh, int fd)
{
	int		status;
	char	*line;

	status = 1;
	while (status > 0)
	{
		status = get_next_line(fd, &line);
		if (status <= 0)
		{
			free(line);
			close(fd);
			exit(msh->code);
		}
		ft_freenewprompt(msh);
		if (ft_parseline(line, msh, 0))
		{
			free(line);
			close(fd);
			exit(2);
		}
		free(line);
		msh->code = ft_forktheforks(msh);
	}
	exit(0);
}

int	ft_periodscript(t_shell *msh, int fd)
{
	int		status;
	int		pid;

	pid = fork();
	if (pid == 0)
	{
		msh->pid = ft_getpid(msh->envp);
		free(msh->tmpdir);
		msh->tmpdir = ft_createtempdir(msh->envp, msh->pid);
		ft_charpptofd(msh->envp, msh);
		msh->envp = ft_fdtocharpp(msh);
		ft_scriptfork(msh, fd);
	}
	waitpid(pid, &status, 0);
	msh->code = WEXITSTATUS(status);
	return (0);
}

int	ft_period(t_commands cmd, t_shell *msh)
{
	int		status;
	int		fd;

	if (cmd.arg[0][1] == '.' && cmd.arg[0][1] == '\0')
		return (ft_errorret("filename argument required", ".", 2));
	else if (cmd.arg[0][1] == '/' || cmd.arg[0][0] == '/')
	{
		status = ft_checkperiod(cmd);
		if (status)
			return (status);
		execve(cmd.abs, cmd.arg, msh->envp);
		fd = open(cmd.abs, O_RDONLY);
		status = ft_periodscript(msh, fd);
		if (fd == -1)
			return (ft_errorret("command not found", cmd.abs, 127));
		close(fd);
		if (status == 2)
			return (2);
		return (msh->code);
	}
	else
		return (ft_errorret("command not found", cmd.arg[0], 127));
	return (0);
}
