/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   test9.c                                         |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: houtworm <codam@houtworm.net>              //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/02/21 03:03:52 by houtworm     /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/02/28 20:38:21 by houtworm     \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../tmp/libft.h"
#include <stdio.h>
#include <string.h>

int	main(void)
{
	int		r;
	char	*s;
	char	*p;

	r = 0;
	s = malloc(8 * 13);
	memcpy(s, "Hello\0\0hello", 12);
	p = ft_memchr(s, 'e', 10);
	if (memcmp(p, "ello\0\0h", 7))
		r = 1;
	free(s);
	return (r);
}
