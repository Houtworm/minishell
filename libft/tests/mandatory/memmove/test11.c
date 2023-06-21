/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   test11.c                                        |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: houtworm <codam@houtworm.net>              //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/02/21 03:00:42 by houtworm     /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/02/28 19:46:23 by houtworm     \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../tmp/libft.h"
#include <stdio.h>
#include <string.h>

int	main(void)
{
	int		r;
	char	*dst;
	char	*src;

	r = 0;
	dst = malloc(8 * 12);
	strcpy(dst, "GHelloHello");
	ft_memmove(&dst[1], dst, 10);
	if (strncmp(dst, "GGHelloHell", 10))
		r = 1;
	free (dst);
	return (r);
}
