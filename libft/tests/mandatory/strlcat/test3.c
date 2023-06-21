/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   test3.c                                            :+:      :+:    :+:   */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: houtworm <codam@houtworm.net>              //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/02/21 02:52:27 by houtworm     /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/03/02 14:46:09 by houtworm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../tmp/libft.h"
#include <stdio.h>
#include <string.h>

int	main(void)
{
	int		ret;
	char	*dst;

	ret = 0;
	dst = malloc(8 * 12);
	memcpy(dst, "yoyoyo\0", 7);
	ft_strlcat(dst, "Hallo\0", 12);
	if (memcmp(dst, "yoyoyoHallo\0", 12))
		ret = 1;
	free(dst);
	return (ret);
}
