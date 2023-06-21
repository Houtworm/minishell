/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   test1.c                                         |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: houtworm <codam@houtworm.net>              //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/02/21 02:59:35 by houtworm     /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/02/23 14:02:14 by houtworm     \___)=(___/                 */
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
	ft_memset(s, '*', 3);
	if (strncmp(s, "***lo", 6))
		r = 1;
	free (s);
	return (r);
}
