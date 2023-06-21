/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   test12.c                                        |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: houtworm <codam@houtworm.net>              //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/02/21 03:00:42 by houtworm     /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/03/03 13:47:05 by houtworm     \___)=(___/                 */
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

	dst = NULL;
	r = 0;
	ft_memmove(dst, "Hello", 5);
	if (dst)
		r = 1;
	return (r);
}
