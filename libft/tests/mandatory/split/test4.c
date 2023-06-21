/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   test4.c                                         |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: houtworm <codam@houtworm.net>              //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/02/21 02:48:46 by houtworm     /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/02/23 15:54:28 by houtworm     \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../tmp/libft.h"
#include <stdio.h>
#include <string.h>

int	main(void)
{
	int		r;
	char	*str3;
	char	*s7;
	char	*s8;
	char	**r3;

	r = 0;
	str3 = "split||th\nis||";
	s7 = "split";
	s8 = "th\nis";
	r3 = ft_split(str3, '|');
	if (strncmp(r3[0], &s7[0], 50) || strncmp(r3[1], &s8[0], 50))
		r = 1;
	free(r3[0]);
	free(r3[1]);
	free(r3);
	return (0);
}
