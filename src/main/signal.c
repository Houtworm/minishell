/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   signal.c                                        |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: houtworm <codam@houtworm.net>              //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/09/19 22:27:48 by houtworm     /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/09/20 00:01:55 by houtworm     \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_sighandler(int sig)
{
	if (sig == SIGINT)
	{
		// stop it from printing ^C on the prompt
		//somehow break the mainloop
	}
	if (sig == SIGQUIT)
	{
		// stop it from printing ^\ on the prompt
		// quit the current child
	}
}
