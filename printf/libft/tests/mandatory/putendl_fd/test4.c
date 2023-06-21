/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   test4.c                                         |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: houtworm <codam@houtworm.net>              //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/02/21 02:58:12 by houtworm     /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/02/23 20:26:15 by houtworm     \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../tmp/libft.h"
#include <stdio.h>

int	main(void)
{
	int		i;
	int		j;
	char	*stri;

	i = 0;
	stri = malloc(8 * 1000000);
	while (i < 999999)
	{
		stri[i] = 'a';
		i++;
	}
	ft_putendl_fd(stri, 1);
	free (stri);
	return (0);
}
