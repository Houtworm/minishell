/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   fork.c                                          |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: houtworm <codam@houtworm.net>              //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/08/24 23:56:01 by houtworm     /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/08/28 10:34:29 by houtworm     \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_forktheforks(t_shell shell)
{
	int	code;
	int	status;
	int forknumber;

	forknumber = 0;
	status = 1;
	shell.starttime = ft_gettimems(shell.envp);
	if (shell.forkamount > 1)
	{
		while (shell.forkamount > forknumber)
		{
			shell.forks[forknumber].pid = fork();
			if (shell.forks[forknumber].pid == 0)
			{
				status = ft_executeforks(shell.forks[forknumber]);
			}
			forknumber++;
			waitpid(shell.forks[forknumber].pid, &status, 0);
			code = WEXITSTATUS(status);
		}
	}
	else
	{
		ft_printf("forknumber here: %s\n", shell.forks[forknumber].pipeline);
		status = ft_executeforks(shell.forks[forknumber]);
	}
	code = WEXITSTATUS(status);
	return (code);
}
