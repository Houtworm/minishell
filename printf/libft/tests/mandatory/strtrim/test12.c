/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   test14.c                                        |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: houtworm <codam@houtworm.net>              //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/02/21 02:37:38 by houtworm     /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/03/02 07:49:59 by djonker      \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../tmp/libft.h"
#include <stdio.h>
#include <string.h>

int	main(void)
{
	int		ret;
	char	*s1;
	char	*set;
	char	*a;
	char	*r;

	ret = 0;
	r = ft_strtrim("Hallo dit is een string", "\0\0");
	if (strncmp(r, "Hallo dit is een string\0", 18))
		ret = 1;
	free (r);
	return (ret);
}
