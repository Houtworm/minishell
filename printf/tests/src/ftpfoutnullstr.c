/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   ftpfoutnullstr.c                                |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: houtworm <codam@houtworm.net>              //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/02/25 17:07:23 by houtworm     /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/03/07 02:34:07 by houtworm     \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../tmp/ft_printf.h"
#include <stdio.h>

int	main(int argc, char **argv)
{
	alarm(5);
	ft_printf("%s", NULL);
	return (0);
}
