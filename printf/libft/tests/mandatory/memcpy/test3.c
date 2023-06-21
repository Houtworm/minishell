/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   test3.c                                         |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: houtworm <codam@houtworm.net>              //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/02/21 03:02:18 by houtworm     /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/02/28 16:57:34 by houtworm     \___)=(___/                 */
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
	dst = malloc(8 * 8);
	src = malloc(8 * 11);
	strcpy(src, "1234567890");
	strcpy(dst, "abcdefg");
	ft_memcpy(dst, src, 6);
	if (strncmp(dst, "123456g", 7))
		r = 1;
	free (dst);
	free (src);
	return (r);
}
