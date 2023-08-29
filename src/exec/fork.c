/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   fork.c                                          |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: houtworm <codam@houtworm.net>              //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/08/24 23:56:01 by houtworm     /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/08/29 03:03:35 by houtworm     \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	**ft_preparepipes(t_shell shell)
{
	int	**pipes;
	int	i;

	i = 0;
	pipes = ft_calloc(sizeof(int *) * (shell.forkamount + 1), 1);
	if (pipes == NULL)
		ft_errorexit("Error allocating memory", "malloc", 1);
	while (i < shell.forkamount)
	{
		pipes[i] = ft_calloc(sizeof(int) * 2, 1);
		if (pipes[i] == NULL)
			ft_errorexit("Error allocating memory", "malloc", 1);
		i++;
	}
	return (pipes);
}

int	ft_forktheforks(t_shell shell)
{
	int	code;
	int	status;
	int forknumber;

	forknumber = 0;
	status = 1;
	shell.starttime = ft_gettimems(shell.envp);
	shell.pipes = ft_preparepipes(shell);
	if (shell.forkamount > 1)
	{
		while (shell.forkamount > forknumber)
		{
			pipe(shell.pipes[forknumber]);
			shell.forks[forknumber].pid = fork();
			if (shell.forks[forknumber].pid == 0)
				status = ft_executeforks(shell.forks[forknumber], forknumber, shell.pipes);
			waitpid(shell.forks[forknumber].pid, &status, 0);
			code = WEXITSTATUS(status);
			close(shell.pipes[forknumber][1]);
			forknumber++;
		}
	}
	else
		status = ft_executeforks(shell.forks[forknumber], forknumber, shell.pipes);
	code = WEXITSTATUS(status);
	return (code);
}
