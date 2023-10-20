/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fork.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: houtworm <codam@houtworm.net>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/24 23:56:01 by houtworm      #+#    #+#                 */
/*   Updated: 2023/10/20 16:15:34 by houtworm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	**ft_preparepipes(t_shell *msh)
{
	int	**pipes;
	int	i;

	i = 0;
	pipes = ft_calloc(sizeof(int *) * (msh->forks + 2), 1);
	if (pipes == NULL)
		ft_errorexit("Error allocating memory", "malloc", 1);
	while (i <= msh->forks + 1)
	{
		pipes[i] = ft_calloc(sizeof(int) * 2, 1);
		if (pipes[i] == NULL)
			ft_errorexit("Error allocating memory", "malloc", 1);
		i++;
	}
	return (pipes);
}

int	ft_checkcondition(t_forks *fork, int mode, int forknbr)
{
	int	ifork;
	int	icmd;

	ifork = 0;
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
		return (0);
	}
	while (fork[ifork].line)
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

int	ft_forktheforks(t_shell *msh)
{
	int		status;
	int		forknumber;
	int		fd;
	char	*file;

	forknumber = 0;
	status = 1;
	if (msh->forks > 1)
	{
		msh->pipes = ft_preparepipes(msh);
		pipe(msh->pipes[forknumber]);
		while (msh->forks > forknumber)
		{
			if (msh->frk[forknumber].waitforlast)
			{
				waitpid(msh->frk[forknumber - 1].pid, &status, 0);
				msh->code = WEXITSTATUS(status);
				file = ft_strjoin(msh->tmpdir, "lastcode.tmp");
				fd = open(file, O_RDONLY);
				free(file);
				if (fd > 0)
				{
					close(fd);
					return (msh->code);
				}
			}
			pipe(msh->pipes[forknumber + 1]);
			msh->frk[forknumber].pid = fork();
			if (msh->frk[forknumber].pid == 0)
				exit (ft_executeforks(forknumber, msh, ft_checkcondition(msh->frk, 0, forknumber)));
			close(msh->pipes[forknumber][1]);
			close(msh->pipes[forknumber][0]);
			forknumber++;
		}
		forknumber = 0;
		while (msh->forks > forknumber)
		{
			close(msh->pipes[forknumber][0]);
			close(msh->pipes[forknumber][1]);
			waitpid(msh->frk[forknumber].pid, &status, 0);
			msh->code = WEXITSTATUS(status);
			forknumber++;
		}
	}
	else
	{
		msh->code = ft_executeforks(forknumber, msh, 0);
	}
	return (msh->code);
}
