/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   signal.c                                        |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: houtworm <codam@houtworm.net>              //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/09/19 22:27:48 by houtworm     /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/09/20 03:15:23 by houtworm     \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_sighandler(int sig)
{
	if (sig == SIGINT) // C //
	{
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
		rl_replace_line("", 2);
		rl_on_new_line();
		// stop it from printing ^C on the prompt
		//somehow break the mainloop
	}
	if (sig == SIGQUIT) // \ //
	{
		// stop it from printing ^\ on the prompt
		// quit the current child
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

