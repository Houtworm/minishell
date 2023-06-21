/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   test5.c                                         |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: houtworm <codam@houtworm.net>              //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/02/21 02:33:32 by houtworm     /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/03/02 06:37:57 by djonker      \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../tmp/libft.h"
#include <stdio.h>

int	main(void)
{
	int	c;

	c = 'Z';
	if (ft_toupper(c) != 'Z')
		return (1);
	return (0);
}
