/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   ftpfoutn.c                                      |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: houtworm <codam@houtworm.net>              //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/02/25 17:07:23 by houtworm     /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/03/01 22:39:14 by djonker      \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../tmp/ft_printf.h"

int	main(int argc, char **argv)
{
	int	i;
	int	*n;

	alarm(5);
	i = atoi(argv[2]);
	n = &i;
	n = malloc(64);
	ft_printf(argv[1], n);
	ft_printf(" %d", i);
	free(n);
	return (0);
}