/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   test7.c                                         |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: houtworm <codam@houtworm.net>              //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/02/21 02:46:32 by houtworm     /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/02/22 05:16:39 by djonker      \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../tmp/libft.h"
#include <stdio.h>

int	main(void)
{
	int	c;

	c = '/';
	if (!ft_isalnum(c))
		return (0);
	return (1);
}
