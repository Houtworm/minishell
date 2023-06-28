/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   test12.c                                        |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: houtworm <codam@houtworm.net>              //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/02/21 02:36:13 by houtworm     /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/03/02 10:50:33 by djonker      \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../tmp/libft.h"
#include <stdio.h>
#include <string.h>

int	main(void)
{
	int		ret;
	char	*r;

	ret = 0;
	r = ft_substr(NULL, 3, 3);
	if (r)
		ret = 1;
	free (r);
	return (ret);
}