/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   test10.c                                        |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: houtworm <codam@houtworm.net>              //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/02/21 02:52:27 by houtworm     /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/03/03 13:58:13 by houtworm     \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../tmp/libft.h"
#include <stdio.h>
#include <string.h>

int	main(void)
{
	int		ret;
	char	*dst;

	ret = 0;
	dst = malloc(8 * 12);
	memcpy(dst, "yoyoyo\0", 7);
	ft_strlcat(dst, NULL, 12);
	if (strncmp(dst, "yoyoyo\0", 7))
		ret = 1;
	free(dst);
	return (ret);
}
