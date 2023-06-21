/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   test7.c                                         |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: houtworm <codam@houtworm.net>              //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/02/21 02:38:36 by houtworm     /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/03/01 06:20:41 by houtworm     \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../tmp/libft.h"
#include <stdio.h>
#include <string.h>

int	main(void)
{
	char	*str;

	str = ft_strchr("hallo", 'h');
	if (memcmp(str, "hallo\0", 6))
		return (1);
	return (0);
}
