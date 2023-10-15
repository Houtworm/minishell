/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   files.c                                         |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: houtworm <codam@houtworm.net>              //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/10/15 05:08:56 by houtworm     /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/10/15 05:16:34 by houtworm     \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_removemshfiles(void)
{
	unlink("/tmp/minishelllastcode.tmp");
	unlink("/tmp/minishelltempz.tmp");
	unlink("/tmp/minishellenvpfile.tmp");
	unlink("/tmp/minishellhistory.tmp");
	unlink("/tmp/minishellprintsem");
	return (0);
}
