/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   ftpfoutchar.c                                   |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: houtworm <codam@houtworm.net>              //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/02/25 17:07:23 by houtworm     /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/03/01 22:38:55 by djonker      \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../tmp/ft_printf.h"
#include <stdio.h>

int	main(int argc, char **argv)
{
	alarm(5);
	ft_printf(argv[1], atoi(argv[2]), argv[3][0]);
	return (0);
}
