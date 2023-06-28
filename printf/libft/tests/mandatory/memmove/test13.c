/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   test13.c                                        |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: houtworm <codam@houtworm.net>              //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/02/21 03:00:42 by houtworm     /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/03/03 13:45:52 by houtworm     \___)=(___/                 */
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
	dst = malloc(8 * 6);
	strcpy(dst, "Olleh");
	ft_memmove(dst, NULL, 1);
	if (strncmp(dst, "Olleh", 6))
		r = 1;
	free (dst);
	return (r);
}