/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   test7.c                                         |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: houtworm <codam@houtworm.net>              //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/02/21 03:02:18 by houtworm     /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/02/28 19:01:35 by houtworm     \___)=(___/                 */
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
	dst = malloc(8 * 7);
	src = malloc(8 * 7);
	memcpy(src, "ab\0\0ef", 6);
	strcpy(dst, "123456");
	ft_memcpy(dst, src, 6);
	if (memcmp(dst, "ab\0\0ef", 6))
		r = 1;
	free (dst);
	free (src);
	return (r);
}
