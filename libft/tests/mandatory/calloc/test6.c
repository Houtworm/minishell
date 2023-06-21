/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   test6.c                                         |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: houtworm <codam@houtworm.net>              //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/02/21 02:47:24 by houtworm     /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/03/03 10:55:09 by houtworm     \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../tmp/libft.h"
#include <stdio.h>
#include <string.h>

int	main(void)
{
	int		rtrn;
	char	*a;

	a = ft_calloc(-1, 1);
	rtrn = 0;
	if (a)
		rtrn = 1;
	return (rtrn);
}
