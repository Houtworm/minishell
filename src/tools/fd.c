/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   fd.c                                            |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: houtworm <codam@houtworm.net>              //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/10/08 02:51:38 by houtworm     /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/10/08 02:51:40 by houtworm     \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_safeclosefd(int	fd)
{
	if (fd > 0)
		close(fd);
}

void	ft_closepipes(t_shell *shell)
{
	int	i;

	i = 0;
	while  (i < shell->forkamount + 1)
	{
		ft_safeclosefd(shell->pipes[i][0]);
		ft_safeclosefd(shell->pipes[i][1]);
		i++;
	}
}

void	ft_restorefds(t_shell *shell)
{
	dup2(shell->stdinfd, 0);
	dup2(shell->stdoutfd, 1);
}
