/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   test1.c                                         |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: houtworm <codam@houtworm.net>              //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/02/21 02:48:46 by houtworm     /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/02/23 15:49:51 by houtworm     \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../tmp/libft.h"
#include <stdio.h>
#include <string.h>

int	main(void)
{
	int		ret;
	char	*s0;
	char	*s4;
	char	**r;

	ret = 0;
	s0 = "split\0";
	s4 = "!\0";
	r = ft_split("split||this|for|me|||||!", '|');
	if (strncmp(r[0], &s0[0], 50) || strncmp(r[4], &s4[0], 50))
		ret = 1;
	free(r[0]);
	free(r[1]);
	free(r[2]);
	free(r[3]);
	free(r[4]);
	free(r[5]);
	free(r);
	return (ret);
}
