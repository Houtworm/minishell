/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fork.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: houtworm <codam@houtworm.net>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/24 23:56:01 by houtworm      #+#    #+#                 */
/*   Updated: 2023/11/11 07:59:17 by houtworm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	**ft_preparepipes(t_shell *msh)
{
	int	**pipes;
	int	i;

	i = 0;
	pipes = ft_calloc(sizeof(int *) * (msh->forks + 2), 1);
	while (i <= msh->forks + 1)
	{
		pipes[i] = ft_calloc(sizeof(int) * 2, 1);
		i++;
	}
	return (pipes);
}

int	ft_checkcond(t_forks *fork, int mode, int forknbr, int ifork)
{
	int	icmd;

	if (!mode)
	{
		icmd = 0;
		ifork = forknbr;
		while (icmd < fork[ifork].cmds)
		{
			if (fork[ifork].cmd[icmd].condition)
				return (1);
			icmd++;
		}
	}
	while (mode && fork[ifork].line)
	{
		icmd = 0;
		while (icmd < fork[ifork].cmds)
		{
			if (fork[ifork].cmd[icmd].condition)
				return (1);
			icmd++;
		}
		ifork++;
	}
	return (0);
}

int	ft_forking(t_shell *msh, int fnbr, int fd, int status)
{
	char	*file;

	while (msh->forks > fnbr)
	{
		if (msh->frk[fnbr].waitforlast)
		{
			waitpid(msh->frk[fnbr - 1].pid, &status, 0);
			g_retcode = WEXITSTATUS(status);
			file = ft_strjoin(msh->tmpdir, "lastcode.tmp");
			fd = open(file, O_RDONLY);
			free(file);
			if (fd > 0 && !close(fd))
				return (g_retcode);
		}
		pipe(msh->pipes[fnbr + 1]);
		msh->frk[fnbr].pid = fork();
		if (msh->frk[fnbr].pid == 0)
			exit (ft_execforks(fnbr, msh, ft_checkcond(msh->frk, 0, fnbr, 0)));
		close(msh->pipes[fnbr][1]);
		close(msh->pipes[fnbr][0]);
		fnbr++;
	}
	return (-1);
}

int	ft_forktheforks(t_shell *msh)
{
	int		status;
	int		fnbr;

	status = 1;
	if (msh->forks > 1)
	{
		msh->pipes = ft_preparepipes(msh);
		pipe(msh->pipes[0]);
		g_retcode = ft_forking(msh, 0, 0, status);
		if (g_retcode >= 0)
			return (g_retcode);
		fnbr = 0;
		while (msh->forks > fnbr)
		{
			close(msh->pipes[fnbr][0]);
			close(msh->pipes[fnbr][1]);
			waitpid(msh->frk[fnbr].pid, &status, 0);
			g_retcode = WEXITSTATUS(status);
			fnbr++;
		}
	}
	else
		g_retcode = ft_execforks(0, msh, 0);
	return (g_retcode);
}
