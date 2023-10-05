/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fork.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: houtworm <codam@houtworm.net>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/24 23:56:01 by houtworm      #+#    #+#                 */
/*   Updated: 2023/10/05 22:27:30 by yitoh         ########   odam.nl         */
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

int	ft_checkcondition(t_forks fork)
{
	int	icmd;

	icmd = 0;
	if (fork.cmdamount < 2)
		return (0);
	while (icmd < fork.cmdamount)
	{
		if (fork.cmds[icmd].condition)
			return (1);
		icmd++;
	}
	return (0);
}

int	ft_checkexec(t_forks fork)
{
	int	icmd;

	icmd = 0;
	while (icmd < fork.cmdamount)
	{
		ft_putstr_fd("  ", 2);
		ft_putnbr_fd(fork.cmds[icmd].lastcode, 2);
		if ((fork.cmds[icmd].condition == 1 && fork.cmds[icmd].lastcode != 0)
			|| (fork.cmds[icmd].condition == 2 && fork.cmds[icmd].lastcode == 0))
			return (1);
		icmd++;
	}
	ft_putendl_fd(" no condition", 2);
	return (0);
}

int	ft_forktheforks(t_shell *shell)
{
	int	status;
	int forknumber;

	forknumber = 0;
	status = 1;
	shell->starttime = ft_gettimems(shell->envp);
	if (shell->forkamount > 1)
	{
		shell->pipes = ft_preparepipes(shell);
		pipe(shell->pipes[forknumber]);
		while (shell->forkamount > forknumber)
		{
			pipe(shell->pipes[forknumber + 1]);
			shell->forks[forknumber].pid = fork();
			if (shell->forks[forknumber].pid == 0)
				exit (ft_executeforks(forknumber, shell));
			// if (ft_checkcondition(shell->forks[forknumber]))
			// {
			// 	waitpid(shell->forks[forknumber].pid, &status, 0);
			// 	shell->code = WEXITSTATUS(status);
			// 	if (shell->code && ft_checkexec(shell->forks[forknumber]))
			// 		return (shell->code);
			// }
			forknumber++;
			close(shell->pipes[forknumber][1]);
		}
		forknumber = 0;
		while (shell->forkamount > forknumber)
		{
			waitpid(shell->forks[forknumber].pid, &status, 0);
			shell->code = WEXITSTATUS(status);
			forknumber++;
		}
	}
	else
	{
		shell->code = ft_executeforks(forknumber, shell);
	}
	return (shell->code);
}
