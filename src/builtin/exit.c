/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   exit.c                                          |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: djonker <djonker@student.codam.nl>         //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/05/18 18:48:08 by djonker      /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/09/15 16:22:33 by djonker      \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_exit(t_cmds cmds)
{
	printf("%s\n", cmds.arguments[1]);
	if (!ft_strncmp(cmds.absolute, "exit\0", 5))
		exit(0);
	if (!ft_strncmp(cmds.absolute, "exit ", 5))
		exit(ft_atoi(cmds.arguments[1]));
	return (0);
}
