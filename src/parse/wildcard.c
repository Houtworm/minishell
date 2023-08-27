/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   wildcard.c                                      |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: houtworm <codam@houtworm.net>              //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/08/27 08:14:23 by houtworm     /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/08/27 10:36:45 by houtworm     \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*This function surely needs some more research.*/
/*How do we get the contents of a folder and expand to everything that matches?*/
/*It will be the first thing on my list when the && || and ; operators are working correctly :)*/

int	ft_parsewildcard(t_cmds cmd)
{
	printf("%s\n", cmd.pipeline);
	return (0);
}
