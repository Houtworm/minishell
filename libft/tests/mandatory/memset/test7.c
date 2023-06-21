/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   test7.c                                         |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: houtworm <codam@houtworm.net>              //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/02/21 02:59:35 by houtworm     /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/02/28 20:11:36 by houtworm     \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../tmp/libft.h"
#include <stdio.h>
#include <string.h>

int	main(void)
{
	int		r;
	char	*s;

	r = 0;
	s = malloc(8 * 6);
	strcpy(s, "Hallo");
	ft_memset(s, '*', 10);
	if (strncmp(s, "**********", 10))
		r = 1;
	free (s);
	return (r);
}
