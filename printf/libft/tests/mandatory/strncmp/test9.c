/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   test9.c                                         |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: houtworm <codam@houtworm.net>              //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/02/21 02:42:46 by houtworm     /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/03/02 05:27:29 by djonker      \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../tmp/libft.h"
#include <stdio.h>
#include <string.h>

int	main(void)
{
	if (!ft_strncmp("\0\0", "Hello", 4))
		return (1);
	return (0);
}
