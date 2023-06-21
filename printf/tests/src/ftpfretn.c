/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   ftpfretn.c                                      |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: houtworm <codam@houtworm.net>              //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/02/25 17:07:23 by houtworm     /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/03/01 22:39:41 by djonker      \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../tmp/ft_printf.h"

int	main(int argc, char **argv)
{
	int	i;
	int	*n;
	int	r;
	int	r2;

	alarm(5);
	i = atoi(argv[2]);
	n = &i;
	n = malloc(64);
	r = ft_printf(argv[1], n);
	r2 = ft_printf(" %d", i);
	free(n);
	return (r + r2);
}
