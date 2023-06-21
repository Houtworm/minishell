/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   test9.c                                         |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: houtworm <codam@houtworm.net>              //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/02/21 02:48:46 by houtworm     /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/02/23 15:57:44 by houtworm     \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../tmp/libft.h"
#include <stdio.h>
#include <string.h>

int	main(void)
{
	int		r;
	char	**temp;
	char	**r9;

	r = 0;
	temp = malloc(8 * 3);
	temp[0] = "split";
	temp[1] = "this";
	temp[2] = NULL;
	r9 = ft_split("split this", ' ');
	if (r9[2] != temp[2])
		r = 1;
	free(r9[0]);
	free(r9[1]);
	free(r9);
	free(temp);
	return (r);
}
