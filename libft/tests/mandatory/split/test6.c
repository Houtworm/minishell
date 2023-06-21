/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   test6.c                                         |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: houtworm <codam@houtworm.net>              //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/02/21 02:48:46 by houtworm     /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/02/23 15:55:40 by houtworm     \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../tmp/libft.h"
#include <stdio.h>
#include <string.h>

int	main(void)
{
	int		r;
	char	**r5;

	r = 0;
	r5 = ft_split("split   thi\tis", ' ');
	if (strncmp(r5[0], "split\0", 6) || strncmp(r5[1], "thi\tis\0", 7))
		r = 1;
	free(r5[0]);
	free(r5[1]);
	free(r5);
	return (r);
}
