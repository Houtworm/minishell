/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   test6.c                                            :+:      :+:    :+:   */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: houtworm <codam@houtworm.net>              //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/02/21 02:53:16 by houtworm     /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/03/01 20:27:02 by houtworm         ###   ########.fr       */
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
	r = ft_strjoin("Dit is een ", "\0\0 Hallo");
	if (strncmp(r, "Dit is een ", 11))
		ret = 1;
	free (r);
	return (ret);
}
