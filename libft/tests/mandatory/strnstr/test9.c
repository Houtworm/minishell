/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   test9.c                                         |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: houtworm <codam@houtworm.net>              //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/02/21 02:40:21 by houtworm     /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/03/02 06:07:55 by djonker      \___)=(___/                 */
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

	h = "Joep\tiedepoepie";
	n = "p\tiede";
	len = 20;
	a = "p\tiedepoepie";
	if (strncmp(ft_strnstr(h, n, len), a, 15))
		return (1);
	return (0);
}
