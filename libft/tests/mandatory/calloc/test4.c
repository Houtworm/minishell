/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   test5.c                                         |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: houtworm <codam@houtworm.net>              //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/02/21 02:47:24 by houtworm     /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/02/22 03:16:01 by djonker      \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../tmp/libft.h"
#include <stdio.h>
#include <string.h>

int	main(void)
{
	int		rtrn;
	char	*a;

	a = ft_calloc(0, 1);
	rtrn = 0;
	if (strncmp(a, "\0\0", 2))
		rtrn = 1;
	free(a);
	return (rtrn);
}