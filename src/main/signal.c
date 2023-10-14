/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signal.c                                        |o_o || |                */
/*                                                     +:+                    */
/*   By: houtworm <codam@houtworm.net>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/19 22:27:48 by houtworm      #+#    #+#                 */
/*   Updated: 2023/10/14 06:53:57 by djonker      \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int ft_sighook(void)
{
	return (1);
}

void	ft_sighandler(int sig)
{
	if (sig == SIGINT)
	{
		rl_replace_line("", 0);
		rl_done = 1;
	}
	if (sig == SIGQUIT)
	{
		ft_putstr_fd("Quit (core dumped)", 0);
	}
}

