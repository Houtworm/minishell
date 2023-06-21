/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   test14.c                                        |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: houtworm <codam@houtworm.net>              //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/02/21 02:58:12 by houtworm     /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/02/23 20:25:07 by houtworm     \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../tmp/libft.h"
#include <stdio.h>

int	main(void)
{
	int		i;
	char	*str;

	i = 32;
	str = malloc(8 * 200);
	while (i < 232)
	{
		str[i - 32] = i;
		i++;
	}
	ft_putendl_fd(str, 2);
	free (str);
	return (0);
}
