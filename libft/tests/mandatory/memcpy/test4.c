/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   test4.c                                         |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: houtworm <codam@houtworm.net>              //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/02/21 03:02:18 by houtworm     /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/02/28 17:08:01 by houtworm     \___)=(___/                 */
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
	dst = malloc(8 * 21);
	src = malloc(8 * 7);
	strcpy(src, "123456");
	strcpy(dst, "abcdefghijklmnopqrst");
	ft_memcpy(dst, src, 10);
	if (strncmp(dst, "123456\0", 7))
		r = 1;
	free (dst);
	free (src);
	return (r);
}
