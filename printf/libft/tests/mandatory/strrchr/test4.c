/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   test4.c                                         |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: houtworm <codam@houtworm.net>              //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/02/21 02:56:39 by houtworm     /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/03/03 14:47:15 by houtworm     \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../tmp/libft.h"
#include <stdio.h>
#include <string.h>

int	main(void)
{
	char	*s;
	int		c;
	char	*a;

	s = "iiooiooo";
	c = 'i';
	a = "iooo";
	if (strncmp(ft_strrchr(s, c), a, 10))
		return (1);
	return (0);
}
