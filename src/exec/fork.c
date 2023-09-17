/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fork.c                                          |o_o || |                */
/*                                                     +:+                    */
/*   By: houtworm <codam@houtworm.net>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/24 23:56:01 by houtworm      #+#    #+#                 */
/*   Updated: 2023/09/17 19:26:50 by houtworm     \___)=(___/                 */
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

int	ft_forktheforks(t_shell *shell)
{
	int	status;
	int forknumber;
	int code;

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
			{
				ft_executeforks(forknumber, shell);
				exit (-1);
			}
			/*if (last fork has a condition bigger than 0)*/
			/*{*/ // this should fix the pipe and condition errors we had.
				/*call waitpid in the last fork*/
				/*if condition = 1 and code = 0 or condition is 2 and code != 0*/
					/*continue*/
				/*else*/
					/*break ;*/
			/*}*/
			forknumber++;
			close(shell->pipes[forknumber][1]);
		}
		forknumber = 0;
		while (shell->forkamount > forknumber)
		{
			waitpid(shell->forks[forknumber].pid, &status, 0);
			code = WEXITSTATUS(status);
			shell->code = code;
			forknumber++;
		}
	}
	else
	{
		code = ft_executeforks(forknumber, shell);
	}
	return (code);
}
