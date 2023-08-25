/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   exit.c                                          |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: djonker <djonker@student.codam.nl>         //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/05/18 18:48:08 by djonker      /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/08/25 03:17:57 by houtworm     \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_exit(t_cmds cmds)
{
	printf("hallo\n");
	if (!ft_strncmp(cmds.absolute, "exit ", 5))
		exit(ft_atoi(cmds.arguments[0]));
	if (!ft_strncmp(cmds.absolute, "exit\0", 5))
		exit(0);
	return (0);
}
