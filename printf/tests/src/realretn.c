/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   realretn.c                                      |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: houtworm <codam@houtworm.net>              //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/02/25 17:07:23 by houtworm     /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/02/27 06:42:52 by houtworm     \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

int	main(int argc, char **argv)
{
	int	i;
	int	*n;
	int	r;
	int	r2;

	i = atoi(argv[2]);
	n = &i;
	n = malloc(64);
	r = printf(argv[1], n);
	r2 = printf(" %d", i);
	free(n);
	return (r + r2);
}
