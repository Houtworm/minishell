/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   test11.c                                        |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: houtworm <codam@houtworm.net>              //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/02/21 02:01:57 by houtworm     /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/02/21 23:02:27 by djonker      \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../tmp/libft.h"
#include <stdio.h>

int	main(void)
{
	char	*str;
	int		a;

	str = "123 456";
	a = 123;
	if (ft_atoi(str) != a)
		return (1);
	return (0);
}