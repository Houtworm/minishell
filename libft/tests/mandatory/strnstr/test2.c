/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   test2.c                                         |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: houtworm <codam@houtworm.net>              //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/02/21 02:40:21 by houtworm     /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/03/02 05:57:00 by djonker      \___)=(___/                 */
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

	h = "Joepiedepoepie";
	n = "piede";
	len = 6;
	if (ft_strnstr(h, n, len))
		return (1);
	return (0);
}
