/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   test6.c                                         |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: houtworm <codam@houtworm.net>              //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/02/21 02:51:24 by houtworm     /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/03/02 03:58:04 by djonker      \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../tmp/libft.h"
#include <stdio.h>
#include <string.h>

int	main(void)
{
	int		r;
	char	*dst;

	r = 0;
	dst = malloc(8 * 11);
	ft_strlcpy(dst, "Hallo", 10);
	if (strncmp(dst, "Hallo\0", 5))
		r = 1;
	free (dst);
	return (r);
}
