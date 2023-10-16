/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   fd.c                                            |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: houtworm <codam@houtworm.net>              //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/10/08 02:51:38 by houtworm     /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/10/16 11:51:22 by houtworm     \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_safeclosefd(int	fd)
{
	if (fd > 0)
		close(fd);
}

void	ft_closepipes(t_shell *msh)
{
	int	i;

	i = 0;
	while  (i < msh->forkamount + 1)
	{
		ft_safeclosefd(msh->pipes[i][0]);
		ft_safeclosefd(msh->pipes[i][1]);
		i++;
	}
}

void	ft_restorefds(t_shell *msh)
{
	dup2(msh->stdinfd, 0);
	dup2(msh->stdoutfd, 1);
}
