/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   test3.c                                         |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: houtworm <codam@houtworm.net>              //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/02/21 02:31:08 by houtworm     /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/02/22 02:10:36 by djonker      \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../tmp/libft.h"
#include <stdio.h>
#include <string.h>

int	main(void)
{
	char	*s;
	int		n;
	char	*a;

	s = "Hallo";
	a = "Hallo";
	n = 0;
	ft_bzero(s, n);
	if (strncmp(s, a, 6))
		return (1);
	return (0);
}
