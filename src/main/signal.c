/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signal.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: houtworm <codam@houtworm.net>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/19 22:27:48 by houtworm      #+#    #+#                 */
/*   Updated: 2023/10/04 00:24:39 by yitoh         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int ft_sighook(void)
{
	return (1);
}

void	ft_sighandler(int sig)
{
	if (sig == SIGINT) // C //
	{
		rl_replace_line("", 0);
		rl_done = 1;
	}
	if (sig == SIGQUIT) // \ //
	{
		ft_putstr_fd("Quit (core dumped)", 0); // not really printing for some reason?
	}
	if (sig == SIGTSTP) // Z //
	{
		sigset_t mask;
		int		mpid;

		mpid = getpid(); // FORBIDDEN FUNCTION REWRITE IT!
		tcsetpgrp(STDIN_FILENO, mpid);
		tcsetpgrp(STDOUT_FILENO, mpid);
		sigemptyset(&mask);
		sigaddset(&mask, SIGTSTP);
		sigprocmask(SIG_UNBLOCK, &mask, NULL);
		signal(SIGTSTP, SIG_DFL);
	}
}

