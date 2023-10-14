/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fork.c                                          |o_o || |                */
/*                                                     +:+                    */
/*   By: houtworm <codam@houtworm.net>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/24 23:56:01 by houtworm      #+#    #+#                 */
/*   Updated: 2023/10/14 04:19:16 by djonker      \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	**ft_preparepipes(t_shell *shell)
{
	int	**pipes;
	int	i;

	i = 0;
	pipes = ft_calloc(sizeof(int *) * (shell->forkamount + 2), 1);
	if (pipes == NULL)
		ft_errorexit("Error allocating memory", "malloc", 1);
	while (i <= shell->forkamount + 1)
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
		while (icmd < fork[ifork].cmdamount)
		{
			if (fork[ifork].cmds[icmd].condition)
				return (1);
			icmd++;
		}
		return (0);
	}
	while (fork[ifork].pipeline)
	{
		icmd = 0;
		while (icmd < fork[ifork].cmdamount)
		{
			if (fork[ifork].cmds[icmd].condition)
				return (1);
			icmd++;
		}
		ifork++;
	}
	return (0);
}

int	ft_forktheforks(t_shell *shell)
{
	int	status;
	int forknumber;
	int	fd;
	/*int	i;*/

	forknumber = 0;
	status = 1;
	shell->starttime = ft_gettimems(shell->envp);
	if (shell->forkamount > 1)
	{
		shell->pipes = ft_preparepipes(shell);
		pipe(shell->pipes[forknumber]);
		while (shell->forkamount > forknumber)
		{
			if (shell->forks[forknumber].waitforlast)
			{
				waitpid(shell->forks[forknumber - 1].pid, &status, 0);
				shell->code = WEXITSTATUS(status);
				fd = open("/tmp/minishelllastcode.tmp", O_RDONLY);
				if (fd > 0) // this condition is invalid, instead we need to identify whether the cmd gets executed or not
				{
					if (fd > 0)
						close(fd); 
					return (shell->code);
				}
			}
			pipe(shell->pipes[forknumber + 1]);
			shell->forks[forknumber].pid = fork();
			if (shell->forks[forknumber].pid == 0)
				exit (ft_executeforks(forknumber, shell, ft_checkcondition(shell->forks, 0, forknumber)));		
			// if (ft_checkcondition(shell->forks, 1, forknumber))
			 /*close(shell->pipes[forknumber][1]); // this one breaks something in the tester*/
			 /*close(shell->pipes[forknumber][0]); // this one breaks osmething in the tester*/
			forknumber++;
			close(shell->pipes[forknumber][1]);
		}
		 close(shell->pipes[forknumber][0]);
		forknumber = 0;
		while (shell->forkamount > forknumber)
		{
			 close(shell->pipes[forknumber][1]);
			 if (forknumber > 0)
			 {
				 close(shell->pipes[forknumber - 1][1]);
				 close(shell->pipes[forknumber - 1][0]);
			 }
			waitpid(shell->forks[forknumber].pid, &status, 0); // old line is replaced by the whole if below, buut I am not sure if it makes a difference
			shell->code = WEXITSTATUS(status);
			forknumber++;
			/*fd = waitpid(-1, &status, 0); // This calls waits too but waits for any child, then compares the pid if it is one of the ones we are waiting for. the difference is that the order doesn't matter now*/
			/*if (fd > 0)*/
			/*{*/
				/*i = 0;*/
				/*while (i < shell->forkamount && shell->forks[i].pid != fd)*/
					/*i++;*/
				/*if (i != shell->forkamount)*/
				/*{*/
					 /*close(shell->pipes[forknumber][1]);*/
					 /*if (forknumber > 0)*/
					 /*{*/
						 /*close(shell->pipes[forknumber - 1][1]);*/
						 /*close(shell->pipes[forknumber - 1][0]);*/
					 /*}*/
					/*if (shell->forkamount - 1 == i)*/
						/*shell->code = WEXITSTATUS(status);*/
					/*forknumber++;*/
				/*}*/
			/*}*/
		}
	}
	else
	{
		shell->code = ft_executeforks(forknumber, shell, 0);
	}
	return (shell->code);
}
