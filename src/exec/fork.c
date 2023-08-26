/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   fork.c                                          |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: houtworm <codam@houtworm.net>              //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/08/24 23:56:01 by houtworm     /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/08/26 03:45:14 by djonker      \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_forktheforks(t_shell *shell)
{
	int	status;
	int forknumber;

	forknumber = 0;
	status = 1;
	shell->starttime = ft_gettimems(shell->envp);
	while (shell->forkamount > forknumber)
	{
		shell->forks[forknumber].pid = fork();
		if (shell->forks[forknumber].pid == 0)
		{
			status = ft_executeforks(shell->forks[forknumber]);
			exit(0);
		}
		forknumber++;
	}
	return (status);
}
