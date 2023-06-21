/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   test8.c                                         |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: houtworm <codam@houtworm.net>              //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/02/21 03:02:18 by houtworm     /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/03/01 01:10:13 by houtworm     \___)=(___/                 */
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
	strcpy(dst, "abcdefg");
	ft_memcpy(dst, NULL, 7);
	if (!memcmp(dst, "abcdef", 6))
		r = 1;
	free (dst);
	return (r);
}
