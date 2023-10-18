/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   files.c                                         |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: djonker <codam@houtworm.net>               //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/10/14 07:15:35 by djonker      /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/10/14 08:29:42 by djonker      \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_removemshfiles(void)
{
	unlink("/tmp/minishelllastcode.tmp");
	unlink("/tmp/minishellprintsem");
	unlink("/tmp/minishellenvpfile.tmp");
	unlink("/tmp/minishelltempz.tmp");
	unlink("/tmp/minishellhistory.tmp");
	return (0);
}
