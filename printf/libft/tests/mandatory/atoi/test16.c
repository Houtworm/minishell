/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   test16.c                                        |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: djonker <djonker@student.codam.nl>         //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/02/21 22:31:27 by djonker      /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/03/03 10:42:38 by houtworm     \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../tmp/libft.h"
#include <stdio.h>
#include <string.h>

int	main(void)
{
	char	*str;
	int		a;

	memcpy(str, "\0\0\0", 3);
	a = 0;
	if (ft_atoi(str) != a)
		return (1);
	return (0);
}
