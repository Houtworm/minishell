/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   test13.c                                        |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: houtworm <codam@houtworm.net>              //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/02/21 02:40:21 by houtworm     /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/03/02 06:24:56 by djonker      \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../tmp/libft.h"
#include <stdio.h>
#include <string.h>

int	main(void)
{
	char	*h;
	char	*n;
	int		len;
	char	*a;

	h = "\0\0";
	n = "\0\0";
	len = 20;
	a = "\0";
	if (strncmp(ft_strnstr(h, n, len), a, 15))
		return (1);
	return (0);
}
