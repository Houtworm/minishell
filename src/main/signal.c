/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signal.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: houtworm <codam@houtworm.net>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/19 22:27:48 by houtworm      #+#    #+#                 */
/*   Updated: 2023/11/11 07:58:09 by houtworm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_sighook(void)
{
	return (1);
}

void	ft_sighandler(int sig)
{
	if (sig == SIGINT)
	{
		rl_replace_line("", 0);
		rl_done = 1;
		g_retcode = 130;
	}
	if (sig == SIGQUIT && rl_done == 1)
	{
		ft_putstr_fd("Quit (core dumped)", 0);
		g_retcode = 131;
	}
}

void	ft_sighandlerheredoc(int sig)
{
	if (sig == SIGINT)
	{
		exit(1);
	}
}
