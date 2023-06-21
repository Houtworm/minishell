/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   test8.c                                         |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: houtworm <codam@houtworm.net>              //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/02/21 02:48:46 by houtworm     /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/02/23 15:57:23 by houtworm     \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../tmp/libft.h"
#include <stdio.h>
#include <string.h>

int	main(void)
{
	int		r;
	char	**temp;
	char	**r8;

	r = 0;
	r8 = ft_split("hallo\0 alles goed?", '\0');
	temp = malloc(sizeof(char *));
	temp[0] = "hallo\0";
	if (strncmp(r8[0], temp[0], 6))
		r = 1;
	free(r8[0]);
	free(r8);
	free(temp);
	return (r);
}
