/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   signal.c                                        |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: houtworm <codam@houtworm.net>              //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/09/19 22:27:48 by houtworm     /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/09/20 01:11:41 by houtworm     \___)=(___/                 */
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
	if (sig == SIGTSTP) // D //
	{
		// stop it from printing ^\ on the prompt
		// quit the current child
	}
	if (sig == SIGTSTP) // Z //
	{
		// stop it from printing ^\ on the prompt
		// quit the current child
	}
}
